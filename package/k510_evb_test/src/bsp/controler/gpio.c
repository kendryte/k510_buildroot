/* Copyright 2018 Canaan Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "gpio.h"
#include "muxpin.h"
#include "utils.h"
#include "interrupt.h"
#define GPIO_MAX_PINNO 32
volatile gpio_t *const gpio = (volatile gpio_t *)GPIO_BASE_ADDR;
int gpio_init(void)
{
  //return sysctl_clock_enable(SYSCTL_CLOCK_GPIO);
	return 0;
}

void gpio_set_drive_mode(uint8_t pin, gpio_drive_mode_t mode)
{
  configASSERT(pin < GPIO_MAX_PINNO);
  int io_number = muxpin_get_io_driving(FUNC_GPIO0 + pin);
  configASSERT(io_number >= 0);
  enum muxpin_pull_e pull;
  uint32_t dir;

  switch (mode)
  {
  case GPIO_DM_INPUT:
    pull = MUXPIN_PULL_NONE;
    dir = 0;
    break;
  case GPIO_DM_INPUT_PULL_DOWN:
    pull = MUXPIN_PULL_DOWN;
    dir = 0;
    break;
  case GPIO_DM_INPUT_PULL_UP:
    pull = MUXPIN_PULL_UP;
    dir = 0;
    break;
  case GPIO_DM_OUTPUT:
    pull = MUXPIN_PULL_DOWN;
    dir = 1;
    break;
  default:
    configASSERT(!"GPIO drive mode is not supported.") break;
  }

  muxpin_set_io_pull(io_number, pull);
  set_gpio_bit(gpio->direction.u32, pin, dir);
}

gpio_pin_value_t gpio_get_pin(uint8_t pin)
{
  configASSERT(pin < GPIO_MAX_PINNO);
  uint32_t dir = get_gpio_bit(gpio->direction.u32, pin);
  volatile uint32_t *reg = dir ? gpio->data_output.u32 : gpio->data_input.u32;
  return get_gpio_bit(reg, pin);
}

void gpio_set_pin(uint8_t pin, gpio_pin_value_t value)
{
  configASSERT(pin < GPIO_MAX_PINNO);
  uint32_t dir = get_gpio_bit(gpio->direction.u32, pin);
  volatile uint32_t *reg = dir ? gpio->data_output.u32 : gpio->data_input.u32;
  configASSERT(dir == 1);
  set_gpio_bit(reg, pin, value);
}

void gpio_set_pin_edge(uint8_t pin, gpio_pin_edge_t edge)
{
  switch (edge)
  {
    case GPIO_PE_FALLING:
        set_gpio_bit(gpio->interrupt_level.u32, pin, 0x1);
        set_gpio_bit(gpio->interrupt_polarity.u32, pin, 0x0);
        set_gpio_bit(gpio->interrupt_bothedge.u32, pin, 0x0);
    break;
    case GPIO_PE_RISING:
        set_gpio_bit(gpio->interrupt_level.u32, pin, 0x1);
        set_gpio_bit(gpio->interrupt_polarity.u32, pin, 0x1);
        set_gpio_bit(gpio->interrupt_bothedge.u32, pin, 0x0);
    break;
    case GPIO_PE_BOTH:
        set_gpio_bit(gpio->interrupt_bothedge.u32, pin, 0x1);
    break;
    case GPIO_PE_LOW:
        set_gpio_bit(gpio->interrupt_level.u32, pin, 0x0);
        set_gpio_bit(gpio->interrupt_polarity.u32, pin, 0x0);
        set_gpio_bit(gpio->interrupt_bothedge.u32, pin, 0x0);
    break;
    case GPIO_PE_HIGH:
        set_gpio_bit(gpio->interrupt_level.u32, pin, 0x0);
        set_gpio_bit(gpio->interrupt_polarity.u32, pin, 0x1);
        set_gpio_bit(gpio->interrupt_bothedge.u32, pin, 0x0);
    break;
    default:
    break;
  }
}
// static plic_instance_t gpio_callback_function[32];
// static int gpio_irq_callback(void *ctx)
// {
//   uint32_t gpio_irq_status = gpio->interrupt_status.u32;
//   for (size_t i = 0; i < 32; i++)
//   {
//     if ((gpio_irq_status >> i) & 1)
//     {
//       if (gpio_callback_function[i].callback != NULL)
//       {
//     	  gpio_callback_function[i].callback(gpio_callback_function[i].ctx);
//       }
//       else
//       {
//         return -1;
//       }
//     }
//   }
//   return 0;
// }