import os
import onnxsim
import onnx
import nncase
import numpy as np
import argparse
import numpy as np


def parse_model_input_output(model_file):
    onnx_model = onnx.load(model_file)
    input_all = [node.name for node in onnx_model.graph.input]
    input_initializer = [node.name for node in onnx_model.graph.initializer]
    input_names = list(set(input_all) - set(input_initializer))
    input_tensors = [
        node for node in onnx_model.graph.input if node.name in input_names]

    # input
    inputs = []
    for _, e in enumerate(input_tensors):
        onnx_type = e.type.tensor_type
        input_dict = {}
        input_dict['name'] = e.name
        input_dict['dtype'] = onnx.mapping.TENSOR_TYPE_TO_NP_TYPE[onnx_type.elem_type]
        input_dict['shape'] = [(i.dim_value if i.dim_value != 0 else d) for i, d in zip(
            onnx_type.shape.dim, [1, 3, 224, 224])]
        inputs.append(input_dict)

    return onnx_model, inputs


def onnx_simplify(model_file):
    onnx_model, inputs = parse_model_input_output(model_file)
    onnx_model = onnx.shape_inference.infer_shapes(onnx_model)
    input_shapes = {}
    for input in inputs:
        input_shapes[input['name']] = input['shape']

    onnx_model, check = onnxsim.simplify(onnx_model, input_shapes=input_shapes)
    assert check, "Simplified ONNX model could not be validated"

    model_file = os.path.join(os.path.dirname(model_file), 'simplified.onnx')
    onnx.save_model(onnx_model, model_file)
    return model_file


def read_model_file(model_file):
    with open(model_file, 'rb') as f:
        model_content = f.read()
    return model_content


def generate_data(shape, batch):
    shape[0] *= batch
    data = np.random.rand(*shape).astype(np.float32)
    return data


def main():
    parser = argparse.ArgumentParser(prog="ncc")
    parser.add_argument("--model", type=str, help='model file')
    parser.add_argument("--quant_type", type=str, help='quant_type:uint8/bf16')
    args = parser.parse_args()
    # 模型路径
    model_file = args.model
    quant_type = args.quant_type
    # 模型的输入shape，用于量化生成校正集，维度要跟input_layout一致
    input_shape = [1, 3, 320, 320]
    target = 'k510'
    # 如果需要uint8模型，写成True（只影响模型内部格式，不控制输入是否为uint8）
    use_ptq = False

    # onnx simplify
    model_file = onnx_simplify(model_file)

    # compile_options
    compile_options = nncase.CompileOptions()
    compile_options.target = target
    # 模型输入格式‘uint8’或者‘float32’
    compile_options.input_type = 'uint8'
    compile_options.dump_ir = True
    compile_options.dump_asm = True
    compile_options.dump_dir = 'tmp'

    # preprocess
    # 是否采用模型做预处理
    compile_options.preprocess = True
    # 输入图像的shape，维度为HWC
    #compile_options.input_shape = [320, 320, 3]
    compile_options.input_shape = [1, 3, 320, 320] #wjx 1.0.0
    # 预处理的mean值，每个channel一个
    compile_options.mean = [0, 0, 0]
    # 预处理的std，每个channel一个
    compile_options.std = [255, 255, 255]
    # 如果输入是‘uint8’格式，输入反量化之后的范围
    compile_options.input_range = [0, 255]
    # 设置输入的layout，onnx默认‘NCHW’即可
    compile_options.input_layout = "NCHW"
    compile_options.output_layout = "NCHW"

    # import_options
    import_options = nncase.ImportOptions()
    

    if quant_type != "bf16":
        # quantize model
        compile_options.quant_type = quant_type
        use_ptq = True

    # compiler
    compiler = nncase.Compiler(compile_options)

    # ptq_options
    if use_ptq:
        ptq_options = nncase.PTQTensorOptions()
        ptq_options.samples_count = 10
        ptq_options.set_tensor_data(generate_data(
            input_shape, ptq_options.samples_count).tobytes())
        compiler.use_ptq(ptq_options)

    # import
    model_content = read_model_file(model_file)
    compiler.import_onnx(model_content, import_options)

    # compile
    compiler.compile()

    # kmodel
    kmodel = compiler.gencode_tobytes()
    output_path = 'od.kmodel'
    with open(output_path, 'wb') as f:
        f.write(kmodel)


if __name__ == '__main__':
    main()
