__int64 __fastcall sub_1BA1D0(int a1, int a2, unsigned __int8 *a3, __int64 a4, _DWORD *a5)
{
  void *v5; // x0
  __int64 v6; // x0
  const char *v8; // [xsp+10h] [xbp-440h]
  int v9; // [xsp+18h] [xbp-438h]
  const char *v10; // [xsp+20h] [xbp-430h]
  int v11; // [xsp+28h] [xbp-428h]
  char v16; // [xsp+428h] [xbp-28h] BYREF
  char v17; // [xsp+429h] [xbp-27h]
  char v18; // [xsp+42Ah] [xbp-26h]
  char v19; // [xsp+42Bh] [xbp-25h]
  char v20; // [xsp+42Ch] [xbp-24h]
  char v21; // [xsp+42Dh] [xbp-23h]
  char v22; // [xsp+430h] [xbp-20h]
  char v23; // [xsp+431h] [xbp-1Fh]
  __int64 v24; // [xsp+438h] [xbp-18h]

  v24 = *(_QWORD *)(_ReadStatusReg(ARM64_SYSREG(3, 3, 13, 0, 2)) + 40);
  v5 = memset(&v16, 0, 6uLL);
  if ( a1 == 0x2000 )
  {
    if ( a2 != 1 )
    {
      switch ( a2 )
      {
        case 2:
          protocol_set_mtu(20LL, 20LL);
          v6 = set_connected_status(0LL);
          protocol_write_clean_resend_buf(v6);
          goto LABEL_403;
        case 100:
          v22 = 3;
          v23 = 2;
          break;
        case 101:
          v22 = 3;
          v23 = 32;
          break;
        case 102:
          v22 = 3;
          v23 = 33;
          break;
        case 103:
          v16 = 3;
          v17 = 38;
          v18 = a3[2];
          break;
        case 104:
          v22 = 3;
          v23 = 1;
          *a5 = protocol_write_set_head();
          goto LABEL_403;
        case 105:
          v22 = 3;
          v23 = 3;
          break;
        case 106:
          v22 = 3;
          v23 = 4;
          break;
        case 107:
          v22 = 3;
          v23 = 16;
          break;
        case 108:
          v22 = 3;
          v23 = 17;
          break;
        case 109:
          v22 = 3;
          v23 = 34;
          break;
        case 110:
          v22 = 3;
          v23 = 35;
          break;
        case 111:
          v22 = 3;
          v23 = 48;
          break;
        case 112:
          v22 = 3;
          v23 = 36;
          break;
        case 113:
          v22 = 3;
          v23 = 37;
          break;
        case 114:
          v22 = 3;
          v23 = 40;
          break;
        case 115:
          v16 = 3;
          v17 = 39;
          v18 = 85;
          v19 = -86;
          v20 = 85;
          v21 = -86;
          break;
        case 116:
          v22 = 3;
          v23 = 41;
          break;
        case 117:
          v22 = 3;
          v23 = 42;
          break;
        case 118:
          v22 = 3;
          v23 = 43;
          break;
        case 119:
          v22 = 3;
          v23 = 44;
          break;
        case 120:
          v22 = 3;
          v23 = 80;
          break;
        case 121:
          v22 = 3;
          v23 = 81;
          break;
        case 122:
          v22 = 3;
          v23 = 82;
          break;
        case 123:
          v22 = 3;
          v23 = 83;
          break;
        case 124:
          v22 = 3;
          v23 = 18;
          break;
        case 125:
          v23 = 19;
          v22 = 3;
          break;
        case 126:
          v23 = 20;
          v22 = 3;
          break;
        case 127:
          v23 = 6;
          v22 = 6;
          break;
        case 128:
          v23 = -20;
          v22 = 3;
          break;
        case 129:
          v23 = 7;
          v22 = 6;
          break;
        case 150:
          v22 = 3;
          v23 = 45;
          break;
        case 151:
          v22 = 3;
          v23 = 46;
          break;
        case 152:
          v22 = 3;
          v23 = 49;
          break;
        case 153:
          v22 = 10;
          v23 = 1;
          break;
        case 154:
          v22 = 3;
          v23 = 50;
          break;
        case 155:
          v23 = 51;
          v22 = 3;
          break;
        case 156:
          v23 = 52;
          v22 = 3;
          break;
        case 157:
          v23 = 53;
          v22 = 3;
          break;
        case 158:
          v23 = 54;
          v22 = 3;
          break;
        case 159:
          v23 = 65;
          v22 = 3;
          break;
        case 160:
          v23 = 66;
          v22 = 3;
          break;
        case 161:
          v23 = 67;
          v22 = 3;
          break;
        case 162:
          v23 = 68;
          v22 = 3;
          break;
        case 163:
          v23 = 69;
          v22 = 3;
          break;
        case 164:
          v22 = 3;
          v23 = 70;
          break;
        case 165:
          v22 = 3;
          v23 = 71;
          break;
        case 166:
          v22 = 3;
          v23 = 72;
          break;
        case 167:
          v22 = 3;
          v23 = 73;
          if ( (protocol_func_auto_activity_pause_switch_not_display_val_set_0xff(v5) & 1) != 0 )
            a3[5] = -1;
          if ( (protocol_func_auto_activity_end_switch_not_display_val_set_0xff() & 1) != 0 )
            a3[6] = -1;
          break;
        case 168:
          v22 = 3;
          v23 = 96;
          break;
        case 169:
          v22 = 11;
          v23 = 1;
          break;
        case 170:
          v22 = 11;
          v23 = 2;
          break;
        case 171:
          v22 = 3;
          v23 = 97;
          break;
        case 172:
          v22 = 3;
          v23 = 47;
          break;
        case 173:
          v22 = 3;
          v23 = -30;
          break;
        case 174:
          v22 = 3;
          v23 = -29;
          break;
        case 175:
          v22 = 3;
          v23 = 85;
          break;
        case 176:
          v22 = 3;
          v23 = -76;
          break;
        case 177:
          v22 = 3;
          v23 = 86;
          break;
        case 178:
          v22 = 3;
          v23 = 87;
          break;
        case 179:
          v22 = 3;
          v23 = -28;
          break;
        case 181:
          v22 = 3;
          v23 = 98;
          break;
        case 182:
          v22 = 3;
          v23 = 99;
          break;
        case 183:
          v22 = 3;
          v23 = -27;
          break;
        case 184:
          v22 = 3;
          v23 = -26;
          break;
        case 185:
          v22 = 3;
          v23 = -25;
          break;
        case 186:
          v22 = 3;
          v23 = -24;
          break;
        case 187:
          v22 = 3;
          v23 = -23;
          break;
        case 188:
          v22 = 3;
          v23 = -22;
          break;
        case 190:
          v22 = 3;
          v23 = -21;
          break;
        case 191:
          v22 = 3;
          v23 = -19;
          break;
        case 192:
          v22 = 3;
          v23 = -17;
          break;
        case 193:
          v22 = 3;
          v23 = -16;
          break;
        case 194:
          v22 = 5;
          v23 = 6;
          break;
        case 195:
          v22 = 3;
          v23 = -15;
          break;
        case 196:
          v22 = 3;
          v23 = -14;
          break;
        case 197:
          v22 = 3;
          v23 = -13;
          break;
        case 198:
          v22 = 3;
          v23 = -11;
          break;
        case 199:
          v22 = 3;
          v23 = 21;
          break;
        case 200:
          v22 = 4;
          v23 = 1;
          *a5 = protocol_write_set_head();
          goto LABEL_403;
        case 201:
          v22 = 4;
          v23 = 2;
          *a5 = protocol_write_set_head();
          goto LABEL_403;
        case 202:
          v22 = 4;
          v23 = 3;
          break;
        case 204:
          v22 = 4;
          v23 = 5;
          protocol_func_table_support_encrypted_code_resend(v5);
          break;
        case 210:
          v22 = 3;
          v23 = 88;
          break;
        case 400:
          v22 = 1;
          v23 = 1;
          break;
        case 401:
          v22 = 1;
          v23 = 2;
          break;
        default:
          if ( a2 != 402 )
          {
            switch ( a2 )
            {
              case 403:
                v22 = -16;
                v23 = 1;
                break;
              case 404:
                v22 = -16;
                v23 = 2;
                break;
              case 405:
                v22 = 3;
                v23 = -47;
                break;
              case 406:
                v22 = -16;
                v23 = 3;
                break;
              case 407:
                v22 = 1;
                v23 = 3;
                break;
              case 408:
                v22 = -16;
                v23 = 4;
                break;
              case 409:
                v22 = -16;
                v23 = 5;
                break;
              case 412:
                v16 = 5;
                v17 = 2;
                v18 = 1;
                break;
              case 415:
                v16 = 5;
                v17 = 5;
                break;
              case 420:
                v16 = 5;
                v17 = 2;
                v18 = 2;
                break;
              case 500:
                v16 = 6;
                v17 = 1;
                v18 = 0;
                protocol_status_set_music_status(500LL);
                break;
              case 501:
                v16 = 6;
                v17 = 1;
                v18 = 1;
                protocol_status_set_music_status(501LL);
                break;
              case 502:
                v16 = 6;
                v17 = 2;
                v18 = 0;
                protocol_status_set_photo_status(502LL);
                break;
              case 503:
                v16 = 6;
                v17 = 2;
                v18 = 1;
                protocol_status_set_photo_status(503LL);
                break;
              case 504:
                v16 = 6;
                v17 = 4;
                v18 = 0;
                protocol_status_set_find_device_status(504LL);
                break;
              case 505:
                v16 = 6;
                v17 = 4;
                v18 = 1;
                protocol_status_set_find_device_status(505LL);
                break;
              case 506:
                v16 = 6;
                v17 = 48;
                break;
              case 511:
                v22 = 6;
                v23 = 50;
                break;
              case 512:
                v22 = 6;
                v23 = 80;
                break;
              case 513:
                v22 = 6;
                v23 = 51;
                break;
              case 516:
                v22 = 6;
                v23 = 103;
                break;
              case 517:
                v22 = 6;
                v23 = 112;
                break;
              default:
                if ( (unsigned int)(a2 - 567) < 3 )
                {
                  v16 = 7;
                  v17 = 1;
                  v18 = a2 - 38;
                  v19 = a3[3];
                  *a5 = protocol_write_set_head();
                  goto LABEL_403;
                }
                switch ( a2 )
                {
                  case 574:
                    v16 = 7;
                    v17 = 3;
                    v18 = 0;
                    break;
                  case 577:
                    v22 = 7;
                    v23 = 64;
                    *a5 = protocol_write_set_head();
                    goto LABEL_403;
                  case 578:
                    v22 = 7;
                    v23 = -96;
                    break;
                  case 579:
                    v22 = 7;
                    v23 = -95;
                    break;
                  case 580:
                    v22 = 7;
                    v23 = 96;
                    *a5 = protocol_write_set_head();
                    goto LABEL_403;
                  case 582:
                    v22 = 7;
                    v23 = 112;
                    *a5 = protocol_write_set_head();
                    goto LABEL_403;
                  case 583:
                    v22 = 7;
                    v23 = 113;
                    *a5 = protocol_write_set_head();
                    goto LABEL_403;
                  case 591:
                    v22 = 7;
                    v23 = 97;
                    *a5 = protocol_write_set_head();
                    goto LABEL_403;
                  case 900:
                    v22 = -1;
                    v23 = 1;
                    break;
                  case 1000:
                    v22 = -79;
                    v23 = 1;
                    break;
                  case 1002:
                    v22 = -79;
                    v23 = 2;
                    break;
                  case 1004:
                    v22 = -79;
                    v23 = 3;
                    break;
                  case 5510:
                    v22 = 3;
                    v23 = -31;
                    break;
                  case 6500:
                    v22 = 10;
                    v23 = 2;
                    break;
                  case 6501:
                    v22 = 10;
                    v23 = 3;
                    break;
                  case 6502:
                    v22 = 10;
                    v23 = 4;
                    break;
                  case 6503:
                    v22 = 10;
                    v23 = 5;
                    break;
                  case 6504:
                    v22 = 10;
                    v23 = 6;
                    break;
                  case 7625:
                    v22 = 17;
                    v23 = 48;
                    break;
                  case 7901:
                    v22 = -86;
                    v23 = -2;
                    break;
                  default:
                    debug_log(
                      1LL,
                      "../../../../src/main/cpp/protocol/base_help/protocol_write.c",
                      "protocol_write_vbus_control",
                      949LL,
                      "warn:protocol write invalid evt:%d",
                      a2);
                    goto LABEL_403;
                }
                break;
            }
          }
          break;
      }
LABEL_174:
      *a5 = protocol_write_set_head();
      goto LABEL_403;
    }
    if ( (get_connected_status(v5) & 1) != 0 )
    {
      debug_log(
        1LL,
        "../../../../src/main/cpp/protocol/base_help/protocol_write.c",
        "protocol_write_vbus_control",
        929LL,
        "warn:connected,skip evt connect");
    }
    else
    {
      ((void (*)(void))protocol_write_clean_resend_buf)();
      protocol_func_table_load_save_table();
    }
  }
  else
  {
    if ( a1 == 8448 )
    {
      switch ( a2 )
      {
        case 205:
          v22 = 4;
          v23 = 6;
          break;
        case 300:
          v22 = 2;
          v23 = 4;
          break;
        case 301:
          v22 = 2;
          v23 = 1;
          break;
        case 302:
          v22 = 2;
          v23 = 2;
          break;
        case 304:
          v22 = 2;
          v23 = -96;
          *a5 = protocol_write_set_head();
          goto LABEL_403;
        case 305:
          v22 = 2;
          v23 = 3;
          break;
        case 306:
          v22 = 2;
          v23 = 16;
          break;
        case 307:
          v22 = 2;
          v23 = 32;
          break;
        case 308:
          v22 = 2;
          v23 = 33;
          break;
        case 309:
          v22 = 9;
          v23 = 7;
          break;
        case 310:
          v22 = 2;
          v23 = -94;
          break;
        case 311:
          v22 = 2;
          v23 = 7;
          break;
        case 312:
          v22 = 2;
          v23 = -93;
          break;
        case 313:
          v22 = 2;
          v23 = -92;
          break;
        case 314:
          v22 = 2;
          v23 = -91;
          break;
        case 315:
          v22 = 2;
          v23 = 17;
          break;
        case 316:
          v22 = 2;
          v23 = 48;
          break;
        case 317:
          v22 = 2;
          v23 = -16;
          break;
        case 318:
          v22 = 2;
          v23 = -90;
          break;
        case 319:
          v22 = 2;
          v23 = 49;
          break;
        case 320:
          v22 = 2;
          v23 = 64;
          break;
        case 321:
          v22 = 2;
          v23 = 5;
          break;
        case 322:
          v22 = 2;
          v23 = -89;
          break;
        case 323:
          v22 = 2;
          v23 = -88;
          break;
        case 324:
          v22 = 2;
          v23 = 96;
          break;
        case 325:
          v22 = 2;
          v23 = -80;
          break;
        case 326:
          v22 = 2;
          v23 = -79;
          break;
        case 327:
          v22 = 2;
          v23 = -78;
          break;
        case 328:
          v22 = 2;
          v23 = -77;
          break;
        case 329:
          v22 = 2;
          v23 = -76;
          break;
        case 330:
          v22 = 2;
          v23 = -75;
          break;
        case 331:
          v22 = 2;
          v23 = 67;
          break;
        case 332:
          v22 = 2;
          v23 = 71;
          break;
        case 333:
          v22 = 2;
          v23 = -74;
          break;
        case 334:
          v22 = 2;
          v23 = -23;
          break;
        case 335:
          v22 = 2;
          v23 = -22;
          break;
        case 336:
          v22 = 2;
          v23 = -21;
          break;
        case 337:
          v22 = 2;
          v23 = -15;
          break;
        case 338:
          v22 = 2;
          v23 = -14;
          break;
        case 339:
          v22 = 2;
          v23 = -12;
          break;
        case 340:
          v22 = 2;
          v23 = -87;
          break;
        case 342:
          v22 = 2;
          v23 = 34;
          break;
        case 343:
          v22 = 2;
          v23 = 70;
          break;
        case 344:
          v22 = 2;
          v23 = 35;
          break;
        case 345:
          v22 = 2;
          v23 = 21;
          break;
        case 348:
          v22 = 2;
          v23 = 72;
          break;
        case 349:
          v22 = 2;
          v23 = 88;
          break;
        case 351:
          v22 = 2;
          v23 = 50;
          break;
        case 352:
          v22 = 2;
          v23 = 51;
          break;
        case 353:
          v22 = 2;
          v23 = 52;
          *a5 = protocol_write_set_head();
          goto LABEL_403;
        case 354:
          v22 = 2;
          v23 = 53;
          *a5 = protocol_write_set_head();
          goto LABEL_403;
        case 356:
          v22 = 2;
          v23 = 89;
          break;
        case 421:
          v22 = 2;
          v23 = -13;
          break;
        case 422:
          v22 = 2;
          v23 = 8;
          break;
        case 423:
          v22 = 2;
          v23 = 99;
          break;
        case 424:
          v22 = 2;
          v23 = 69;
          break;
        case 425:
          v22 = 2;
          v23 = 68;
          break;
        case 1006:
          v22 = -79;
          v23 = 4;
          break;
        case 1008:
          v22 = -79;
          v23 = 5;
          break;
        default:
          goto LABEL_403;
      }
      goto LABEL_174;
    }
    if ( a1 == 8704 && a3 )
    {
      if ( (protocol_sync_config_get_is_run(v5) & 1) != 0
        && *a3 == (unsigned __int8)byte_101E978
        && a3[1] == (unsigned __int8)byte_101E979 )
      {
        v11 = dword_101E990;
        v10 = (const char *)protocol_util_vbus_evt_to_str((unsigned int)dword_101E990);
        debug_log(
          1LL,
          "../../../../src/main/cpp/protocol/base_help/protocol_write.c",
          "protocol_write_vbus_control",
          1282LL,
          "stop resend evt:%d(%s)",
          v11,
          v10);
        app_timer_stop((unsigned int)dword_101E970);
        byte_5C0292 = 1;
        byte_101E974 = 0;
        if ( a5 )
          *a5 = sub_1B9CEC();
      }
      if ( *a3 == (unsigned __int8)byte_101E994 && a3[1] == (unsigned __int8)byte_101E995 )
      {
        v9 = dword_101E9AC;
        v8 = (const char *)protocol_util_vbus_evt_to_str((unsigned int)dword_101E9AC);
        debug_log(
          1LL,
          "../../../../src/main/cpp/protocol/base_help/protocol_write.c",
          "protocol_write_vbus_control",
          1293LL,
          "stop resend evt:%d(%s)",
          v9,
          v8);
        app_timer_stop((unsigned int)dword_101E508);
        byte_5C0291 = 1;
        byte_101E50C = 0;
        if ( a5 )
          *a5 = sub_1B9EA8();
      }
    }
  }
LABEL_403:
  _ReadStatusReg(ARM64_SYSREG(3, 3, 13, 0, 2));
  return 0LL;
}