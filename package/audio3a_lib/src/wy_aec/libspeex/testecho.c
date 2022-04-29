#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#if 0
#include "speex/speex_echo.h"
#include "speex/speex_preprocess.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


#define NN 256
#define TAIL 1024

int main(int argc, char **argv)
{
   FILE *echo_fd, *rec_fd, *e_fd;
   //short echo_buf[NN], rec_buf[NN], e_buf[NN];
   short *echo_buf, *rec_buf, *e_buf;
   SpeexEchoState *st;
   SpeexPreprocessState *den;
   int sampleRate = 8000;
   int frameSize = 256;
   int filterLen = 1600;


//   WAV_HEADER echo_header, ref_header;
   int frame_cnt = 0;

//   if (argc != 4)
//   {
//      fprintf(stderr, "testecho mic_signal.sw speaker_signal.sw output.sw\n");
//      exit(1);
//   }
   rec_fd = fopen("01_mic_clvl12.raw", "rb");
   echo_fd = fopen("01_spk_clvl12.raw", "rb");
   e_fd    = fopen("01_res_clvl12.raw", "wb");

//    frameSize = 20 * sampleRate / 1000; // 20ms
   filterLen = frameSize * 10; // 200ms

   rec_buf = (short*)malloc(sizeof(short) * frameSize);
   echo_buf = (short*)malloc(sizeof(short) * frameSize);
   e_buf = (short*)malloc(sizeof(short) * frameSize);

   st = speex_echo_state_init(frameSize, filterLen);
   den = speex_preprocess_state_init(frameSize, sampleRate);
   speex_echo_ctl(st, SPEEX_ECHO_SET_SAMPLING_RATE, &sampleRate);
   speex_preprocess_ctl(den, SPEEX_PREPROCESS_SET_ECHO_STATE, st);

   while (!feof(rec_fd) && !feof(echo_fd))
   {
      fread(rec_buf, sizeof(short), NN, rec_fd);
      fread(echo_buf, sizeof(short), NN, echo_fd);
//	   read_samples(rec_buf, frameSize, &ref_header, rec_fd);
//	   read_samples(echo_buf, frameSize, &echo_header, echo_fd);
       
      speex_echo_cancellation(st, rec_buf, echo_buf, e_buf);
//      speex_preprocess_run(den, rec_buf);

       //speex_echo_playback(st, echo_buf);
       //speex_echo_capture(st, rec_buf, e_buf);

      fwrite(e_buf, sizeof(short), NN, e_fd);
//	  write_samples(e_buf, frameSize, &ref_header, e_fd);
	  printf("Frame %d\n", frame_cnt++);
   }
   speex_echo_state_destroy(st);
   speex_preprocess_state_destroy(den);
   fclose(e_fd);
   fclose(echo_fd);
   fclose(rec_fd);
   free(echo_buf);
   free(rec_buf);
   free(e_buf);
   return 0;
}
#endif
