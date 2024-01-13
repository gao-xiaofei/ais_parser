
#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "nmea.h"
#include "portable.h"
#include "sixbit.h"
#include "vdm_parse.h"

const char *buf[255] = {
    "!AIVDM,1,1,,B,19NS7Sp02wo?HETKA2K6mUM20<L=,0*27\r\n",
    "!AIVDM,2,1,9,A,55Mf@6P00001MUS;7GQL4hh61L4hh6222222220t41H,0*49\r\n",
    "!AIVDM,2,2,9,A,==40HtI4i@E531H1QDTVH51DSCS0,2*16\r\n",
    /* Out of order 2nd part */
    "!AIVDM,3,1,4,B,53nFBv01SJ<thHp6220H4heHTf2222222222221?50:454o<`9QSlUDp,0*"
    "05\r\n",
    "!AIVDM,3,3,4,B,==40HtI4i@E531H1QDTVH51DSCS0,2*18\r\n",
    /* Out of sequence, good part # */
    "!AIVDM,2,1,3,B,55P5TL01VIaAL@7WKO@mBplU@<PDhh000000001S;AJ::4A80?4i@E53,0*"
    "3E\r\n",
    "!AIVDM,2,2,7,B,1@0000000000000,2*51\r\n",
    /* No start to the sequence */
    "!BSVDM,2,2,4,A,54SkDki@000,2*06\r\n",
    /* Good part # and sequence, wrong channel */
    "!AIVDM,2,1,9,A,55Mf@6P00001MUS;7GQL4hh61L4hh6222222220t41H,0*49\r\n",
    "!AIVDM,2,2,9,B,==40HtI4i@E531H1QDTVH51DSCS0,2*15\r\n",
    /* Wrong part #, wrong sequence */
    "!AIVDM,2,1,3,B,55P5TL01VIaAL@7WKO@mBplU@<PDhh000000001S;AJ::4A80?4i@E53,0*"
    "3E\r\n",
    "!AIVDM,2,1,5,B,1@0000000000000,2*50\r\n",
};

int main(void) {
  char *aline = NULL;

  ais_state ais;
  unsigned int i = 0;
  int err;

  aismsg_1 msg_1;
  aismsg_2 msg_2;
  aismsg_3 msg_3;
  aismsg_4 msg_4;
  aismsg_5 msg_5;
  aismsg_12 msg_12;
  aismsg_18 msg_18;
  aismsg_24 msg_24;
  aismsg_27 msg__27;

  memset(&ais, 0, sizeof ais);
  while (1) {
    usleep(1000 * 1000);
    aline = buf[i++];
    if (i > 11) i = 0;
    printf("/*------------------ parser start -------------------------*/\n");
    printf("read:%s\n", aline);

    if ((err = assemble_vdm(&ais, aline)) != 0) {
      printf("parser error %d\n", err);
      continue;
    }
    ais.msgid = (unsigned char)get_6bit(&ais.six_state, 6);

    /* Process the AIS message */
    printf("msgid : %d\n", ais.msgid);

    /* process message with appropriate parser */
    switch (ais.msgid) {
      case 1:
        if (parse_ais_1(&ais, &msg_1) == 0) {
          printf("repeat      : %d\n", msg_1.repeat);
          printf("userid      : %ld\n", msg_1.userid);
          printf("nav_status  : %d\n", msg_1.nav_status);
          printf("rot         : %d\n", msg_1.rot);
          printf("sog         : %d\n", msg_1.sog);
          printf("pos_acc     : %d\n", msg_1.pos_acc);
          printf("longitude   : %lf\n", (double)msg_1.longitude / 600000.0);
          printf("latitude    : %lf\n", (double)msg_1.latitude / 600000.0);
          printf("cog         : %d\n", msg_1.cog);
          printf("true        : %d\n", msg_1._true);
          printf("utc_sec     : %d\n", msg_1.utc_sec);
          printf("regional    : %d\n", msg_1.regional);
          printf("spare       : %d\n", msg_1.spare);
          printf("raim        : %d\n", msg_1.raim);
          printf("sync_state  : %d\n", msg_1.sync_state);
          printf("slot_timeout: %d\n", msg_1.slot_timeout);
          printf("sub_message : %d\n", msg_1.sub_message);
        }
        break;
      case 2:
        break;
      case 3:
        if (parse_ais_3(&ais, &msg_3) == 0) {
          printf("repeat      : %d\n", msg_3.repeat);
          printf("userid      : %ld\n", msg_3.userid);
          printf("nav_status  : %d\n", msg_3.nav_status);
          printf("rot         : %d\n", msg_3.rot);
          printf("sog         : %d\n", msg_3.sog);
          printf("pos_acc     : %d\n", msg_3.pos_acc);
          printf("longitude   : %lf\n", (double)msg_3.longitude / 600000.0);
          printf("latitude    : %lf\n", (double)msg_3.latitude / 600000.0);
          printf("cog         : %d\n", msg_3.cog);
          printf("true        : %d\n", msg_3._true);
          printf("utc_sec     : %d\n", msg_3.utc_sec);
          printf("regional    : %d\n", msg_3.regional);
          printf("spare       : %d\n", msg_3.spare);
          printf("raim        : %d\n", msg_3.raim);
          printf("sync_state  : %d\n", msg_3.sync_state);
          printf("slot_inc    : %d\n", msg_3.slot_increment);
          printf("num_slots   : %d\n", msg_3.num_slots);
          printf("keep        : %d\n", msg_3.keep);
        }

        break;
      case 4:
        break;
        // ......
      default:
        break;
    }
    printf("\n");
  }

  return 0;
}