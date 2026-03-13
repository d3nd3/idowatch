/**
 * IDO / VeryFit SDK Function Tables — bitwise capability flags
 *
 * Complete mapping of all 42 function tables from the SDK header.
 * Part 1 (Tables 1–17): Normal/Base function table — fits in original low-payload
 *   BLE packets. Bit 6 in Table 5 (exFuncTable) triggers fetch of Part 2.
 * Part 2 (Tables 18–42): Extended function table — V3 protocols, smart features,
 *   regional integrations; requested when exFuncTable is set.
 *
 * Usage: GET 0x02 0x02 returns base table; GET 0x02 0x07 returns extended table
 *   when device reports exFuncTable.
 */

#ifndef IDO_FUNC_TABLES_H
#define IDO_FUNC_TABLES_H

#ifdef __cplusplus
extern "C" {
#endif

/* ---------------------------------------------------------------------------
 * PART 1: Normal (Base) Function Tables (1 – 17)
 * --------------------------------------------------------------------------- */

/* Table 1 — Lang 1 */
#define IDO_T1_CH         (1u << 0)  /* Chinese */
#define IDO_T1_ENG        (1u << 1)  /* English */
#define IDO_T1_FRENCH     (1u << 2)  /* French */
#define IDO_T1_GERMAN     (1u << 3)  /* German */
#define IDO_T1_ITALIAN    (1u << 4)  /* Italian */
#define IDO_T1_SPANISH    (1u << 5)  /* Spanish */
#define IDO_T1_JAPANESE   (1u << 6)  /* Japanese */
#define IDO_T1_CZECH      (1u << 7)  /* Czech */

/* Table 2 — Lang 2 */
#define IDO_T2_ROMANIAN     (1u << 0)  /* Romanian */
#define IDO_T2_LITHUANIAN   (1u << 1)  /* Lithuanian */
#define IDO_T2_DUTCH        (1u << 2)  /* Dutch */
#define IDO_T2_SLOVENIAN    (1u << 3)  /* Slovenian */
#define IDO_T2_HUNGARIAN    (1u << 4)  /* Hungarian */
#define IDO_T2_POLISH       (1u << 5)  /* Polish */
#define IDO_T2_RUSSIAN      (1u << 6)  /* Russian */
#define IDO_T2_UKRAINIAN    (1u << 7)  /* Ukrainian */

/* Table 3 — Lang 3 */
#define IDO_T3_SLOVAK      (1u << 0)  /* Slovak */
#define IDO_T3_DANISH      (1u << 1)  /* Danish */
#define IDO_T3_CROATIAN    (1u << 2)  /* Croatian */
#define IDO_T3_INDONESIAN  (1u << 3)  /* Indonesian */
#define IDO_T3_KOREAN      (1u << 4)  /* Korean */
#define IDO_T3_HINDI       (1u << 5)  /* Hindi */
#define IDO_T3_PORTUGUESE  (1u << 6)  /* Portuguese */
#define IDO_T3_TURKISH     (1u << 7)  /* Turkish */

/* Table 4 — Core */
#define IDO_T4_STEP_CALCULATION (1u << 0)  /* Step counting */
#define IDO_T4_SLEEP_MONITOR   (1u << 1)  /* Sleep detection */
#define IDO_T4_SINGLE_SPORT    (1u << 2)  /* Single sport recording */
#define IDO_T4_REALTIME_DATA   (1u << 3)  /* Real-time data sync */
#define IDO_T4_DEVICE_UPDATE   (1u << 4)  /* Device firmware update (OTA) */
#define IDO_T4_HEART_RATE      (1u << 5)  /* Heart rate feature */
#define IDO_T4_ANCS            (1u << 6)  /* Apple Notification Center Service (ANCS) */
#define IDO_T4_TIME_LINE       (1u << 7)  /* Timeline */

/* Table 5 — System */
#define IDO_T5_TAKE_PHOTO   (1u << 0)  /* Take photo control */
#define IDO_T5_MUSIC        (1u << 1)  /* Music control */
#define IDO_T5_HID_PHOTO    (1u << 2)  /* HID photo control */
#define IDO_T5_FIVE_HR_INTERVAL (1u << 3)  /* 5 heart rate intervals */
#define IDO_T5_BIND_AUTH    (1u << 4)  /* Binding Authorization */
#define IDO_T5_FAST_SYNC    (1u << 5)  /* Fast synchronization */
#define IDO_T5_EX_FUNC_TABLE (1u << 6)  /* Extended Features Flag (triggers Part 2) */
#define IDO_T5_BIND_CODE_AUTH (1u << 7)  /* Binding code authorization */

/* Table 6 — Alarms */
#define IDO_T6_WAKE_UP     (1u << 0)   /* Wake up */
#define IDO_T6_SLEEP       (1u << 1)   /* Sleep */
#define IDO_T6_SPORT       (1u << 2)   /* Exercise */
#define IDO_T6_MEDICINE    (1u << 3)   /* Taking medicine */
#define IDO_T6_DATING      (1u << 4)   /* Dating */
#define IDO_T6_PARTY       (1u << 5)   /* Party */
#define IDO_T6_MEETING     (1u << 6)   /* Meeting */
#define IDO_T6_CUSTOM      (1u << 7)   /* Custom */
#define IDO_T6_DINNER      (1u << 8)   /* Dinner */
#define IDO_T6_BRUSH_TEETH (1u << 9)   /* Brush teeth */
#define IDO_T6_REST        (1u << 10)  /* Rest */
#define IDO_T6_COURSE      (1u << 11)  /* Course */
#define IDO_T6_SHOWER      (1u << 12)  /* Shower */
#define IDO_T6_LEARNING    (1u << 13)  /* Learning */
#define IDO_T6_PLAY_TIME   (1u << 14)  /* Play time */

/* Table 7 — Calls */
#define IDO_T7_CALLING            (1u << 0)  /* Incoming call reminder */
#define IDO_T7_CALLING_CONTACT    (1u << 1)  /* Caller contact name */
#define IDO_T7_CALLING_NUM        (1u << 2)  /* Caller phone number */
#define IDO_T7_SUPPORT_FAHRENHEIT (1u << 3)  /* Support Fahrenheit temperature */
#define IDO_T7_V3_FUNCTION_TABLE  (1u << 4)  /* V3 protocol flag */
#define IDO_T7_SCREEN_BRIGHT_INTERVAL (1u << 5)  /* Custom screen brightness duration */

/* Table 8 — Social 1 */
#define IDO_T8_MESSAGE    (1u << 0)  /* SMS */
#define IDO_T8_EMAIL      (1u << 1)  /* Email */
#define IDO_T8_QQ         (1u << 2)  /* QQ */
#define IDO_T8_WEIXIN     (1u << 3)  /* WeChat */
#define IDO_T8_SINA_WEIBO (1u << 4)  /* Sina Weibo */
#define IDO_T8_FACEBOOK   (1u << 5)  /* Facebook */
#define IDO_T8_TWITTER   (1u << 6)  /* Twitter */

/* Table 9 — Social 2 */
#define IDO_T9_WHATSAPP     (1u << 0)  /* WhatsApp */
#define IDO_T9_MESSENGER   (1u << 1)  /* Messenger */
#define IDO_T9_INSTAGRAM   (1u << 2)  /* Instagram */
#define IDO_T9_LINKEDIN    (1u << 3)  /* LinkedIn */
#define IDO_T9_CALENDAR    (1u << 4)  /* Calendar */
#define IDO_T9_SKYPE       (1u << 5)  /* Skype */
#define IDO_T9_ALARM_CLOCK (1u << 6)  /* Alarm Clock (App sync) */
#define IDO_T9_OTHER_REMINDER (1u << 7)  /* Other generic reminders */

/* Table 10 — Social 3 */
#define IDO_T10_VKONTAKTE (1u << 0)  /* VKontakte */
#define IDO_T10_LINE      (1u << 1)  /* LINE */
#define IDO_T10_VIBER     (1u << 2)  /* Viber */
#define IDO_T10_KAKAOTALK (1u << 3)  /* KakaoTalk */
#define IDO_T10_GMAIL     (1u << 4)  /* Gmail */
#define IDO_T10_OUTLOOK   (1u << 5)  /* Outlook */
#define IDO_T10_SNAPCHAT  (1u << 6)  /* Snapchat */
#define IDO_T10_TELEGRAM  (1u << 7)  /* Telegram */

/* Table 11 — Tools */
#define IDO_T11_SEDENTARINESS   (1u << 0)  /* Sedentary reminder */
#define IDO_T11_ANTILOST        (1u << 1)  /* Anti-lost reminder */
#define IDO_T11_ONETOUCH_CALLING (1u << 2)  /* One-touch calling */
#define IDO_T11_FIND_PHONE      (1u << 3)  /* Find phone feature */
#define IDO_T11_FIND_DEVICE     (1u << 4)  /* Find device (band) feature */
#define IDO_T11_CONFIG_DEFAULT  (1u << 5)  /* Default config mode */
#define IDO_T11_UP_HAND_GESTURE (1u << 6)  /* Raise wrist to wake screen */
#define IDO_T11_WEATHER         (1u << 7)  /* Weather forecast */

/* Table 12 — GPS/Msg */
#define IDO_T12_TIP_INFO_CONTACT   (1u << 0)  /* Tip message contact */
#define IDO_T12_TIP_INFO_NUM       (1u << 1)  /* Tip message number */
#define IDO_T12_TIP_INFO_CONTENT   (1u << 2)  /* Tip message content */
#define IDO_T12_SET_V3_HEART_INTERVAL (1u << 3)  /* Set V3 HR interval */
#define IDO_T12_AGPS_ON_LINE       (1u << 4)  /* AGPS Online upgrade */
#define IDO_T12_AGPS_OFF_LINE      (1u << 5)  /* AGPS Offline upgrade */
#define IDO_T12_WEATHER_CITY      (1u << 6)   /* Display weather city */

/* Table 13 — Modes */
#define IDO_T13_STATIC_HR          (1u << 0)  /* Static heart rate */
#define IDO_T13_DO_NOT_DISTURB     (1u << 1)  /* Do Not Disturb (DND) */
#define IDO_T13_DISPLAY_MODE       (1u << 2)  /* Display mode */
#define IDO_T13_HEART_RATE_MONITOR (1u << 3)  /* Auto HR monitoring */
#define IDO_T13_BILATERAL_ANTI_LOST (1u << 4)  /* Two-way anti-lost */
#define IDO_T13_ALL_APP_NOTICE     (1u << 5)  /* Catch-all app notification */
#define IDO_T13_NO_SHOW_HR_INTERVAL (1u << 6)  /* Hide HR intervals */
#define IDO_T13_FLIP_SCREEN        (1u << 7)  /* Flip screen orientation */

/* Table 14 — Sport 1 */
#define IDO_T14_WALK            (1u << 0)  /* Walk */
#define IDO_T14_RUN             (1u << 1)  /* Run */
#define IDO_T14_BY_BIKE         (1u << 2)  /* Bike riding */
#define IDO_T14_ON_FOOT         (1u << 3)  /* Hiking / On foot */
#define IDO_T14_SWIM            (1u << 4)  /* Swim */
#define IDO_T14_MOUNTAIN_CLIMBING (1u << 5)  /* Mountain climbing */
#define IDO_T14_BADMINTON       (1u << 6)  /* Badminton */
#define IDO_T14_OTHER           (1u << 7)  /* Other sport */

/* Table 15 — Sport 2 */
#define IDO_T15_FITNESS      (1u << 0)  /* Fitness */
#define IDO_T15_SPINNING     (1u << 1)  /* Spinning */
#define IDO_T15_ELLIPSOID    (1u << 2)  /* Elliptical */
#define IDO_T15_TREADMILL    (1u << 3)  /* Treadmill */
#define IDO_T15_SIT_UP       (1u << 4)  /* Sit-ups */
#define IDO_T15_PUSH_UP      (1u << 5)  /* Push ups */
#define IDO_T15_DUMBBELL     (1u << 6)  /* Dumbbell */
#define IDO_T15_WEIGHTLIFTING (1u << 7)  /* Weightlifting */

/* Table 16 — Sport 3 */
#define IDO_T16_BODYBUILDING_EXERCISE (1u << 0)   /* Aerobics */
#define IDO_T16_YOGA                 (1u << 1)   /* Yoga */
#define IDO_T16_ROPE_SKIPPING        (1u << 2)   /* Rope skipping */
#define IDO_T16_TABLE_TENNIS         (1u << 3)   /* Table Tennis / Pingpong */
#define IDO_T16_BASKETBALL           (1u << 4)   /* Basketball */
#define IDO_T16_FOOTBALL            (1u << 5)   /* Football */
#define IDO_T16_VOLLEYBALL          (1u << 6)   /* Volleyball */
#define IDO_T16_TENNIS              (1u << 7)   /* Tennis */
#define IDO_T16_SKATEBOARD          (1u << 8)   /* Skateboard */
#define IDO_T16_MOUNTAINEERING      (1u << 9)   /* Mountaineering */
#define IDO_T16_SQUAT               (1u << 10)  /* Squat */
#define IDO_T16_PICKLEBALL          (1u << 11)  /* Pickleball */
#define IDO_T16_AEROBICS_BODYBUILDING_EXERCISE (1u << 12)  /* Aerobics bodybuilding exercise */

/* Table 17 — Sport 4 */
#define IDO_T17_GOLF    (1u << 0)  /* Golf */
#define IDO_T17_BASEBALL (1u << 1)  /* Baseball */
#define IDO_T17_SKIING   (1u << 2)  /* Skiing */
#define IDO_T17_ROLLER_SKATING (1u << 3)  /* Roller skating */
#define IDO_T17_DANCE    (1u << 4)  /* Dancing */
#define IDO_T17_FUNCTIONAL_TRAINING (1u << 5)  /* Functional / Strength training */
#define IDO_T17_CORE_TRAINING (1u << 6)  /* Core training */
#define IDO_T17_TIDY_UP_RELAX (1u << 7)  /* Tidy up / Relax */
#define IDO_T17_TRADITIONAL_STRENGTH_TRAINING (1u << 8)  /* Traditional strength training */

/* ---------------------------------------------------------------------------
 * PART 2: Extended (Ex) Function Tables (18 – 42)
 * --------------------------------------------------------------------------- */

/* Table 18 — Setup */
#define IDO_T18_LOG_IN          (1u << 0)  /* Login support */
#define IDO_T18_HID_PHOTO       (1u << 1)  /* Bracelet takes pictures */
#define IDO_T18_WATCH_DIAL      (1u << 2)  /* Watch dial face support */
#define IDO_T18_SHORTCUT        (1u << 3)  /* Shortcut menus */
#define IDO_T18_UNIT_SET        (1u << 4)  /* Separate unit settings */
#define IDO_T18_BLOOD_PRESSURE  (1u << 5)  /* Blood pressure reading */
#define IDO_T18_WECHAT_SPORT    (1u << 6)  /* WeChat Sport syncing */
#define IDO_T18_FINE_TIME_CONTROL (1u << 7)  /* Fine time period control */

/* Table 19 — Hardware */
#define IDO_T19_GPS              (1u << 0)  /* Built-in GPS */
#define IDO_T19_SLEEP_PERIOD     (1u << 1)  /* Sleep period data */
#define IDO_T19_SCREEN_BRIGHTNESS (1u << 2)  /* Screen brightness */
#define IDO_T19_ID107_DIAL       (1u << 3)  /* Legacy id107l dial */
#define IDO_T19_DH_NEW_APP_NOTICE (1u << 4)  /* dhNewAppNotice */
#define IDO_T19_NOTICE_128_BYTE   (1u << 5)  /* 128-byte notification */
#define IDO_T19_ACTIVITY_TIME_SYNC (1u << 6)  /* Time synchronization */
#define IDO_T19_V3_LOG           (1u << 7)  /* V3 system log collection */

/* Table 20 — Health */
#define IDO_T20_MENSTRUATION   (1u << 0)  /* Female menstrual cycle */
#define IDO_T20_CALORIE_GOAL   (1u << 1)  /* Calorie targets */
#define IDO_T20_DISTANCE_GOAL  (1u << 2)  /* Distance targets */
#define IDO_T20_SPO2_DATA      (1u << 3)  /* Blood oxygen (SpO2) data */
#define IDO_T20_PRESSURE_DATA  (1u << 4)  /* Stress/Pressure data */
#define IDO_T20_GET_NO_DISTURB (1u << 5)  /* Get DND config */
#define IDO_T20_SPORT_MODE_SORT (1u << 6)  /* Sortable sport modes */
#define IDO_T20_NOTICE_BYTE    (1u << 7)  /* 250-byte notification payload */

/* Table 21 — Apps */
#define IDO_T21_CHATWORK   (1u << 0)  /* Chatwork */
#define IDO_T21_SLACK      (1u << 1)  /* Slack */
#define IDO_T21_TUMBLR     (1u << 2)  /* Tumblr */
#define IDO_T21_YOUTUBE    (1u << 3)  /* YouTube */
#define IDO_T21_YAHOO_PINTEREST (1u << 4)  /* Yahoo / Pinterest */
#define IDO_T21_YAHOO_MAIL (1u << 5)  /* Yahoo Mail */
#define IDO_T21_KEEP       (1u << 6)  /* Google Keep */
#define IDO_T21_STEPPER    (1u << 7)  /* Stepper machine (Sport) */

/* Table 22 — V3 Data */
#define IDO_T22_AUTO_PAIR         (1u << 0)  /* Auto pair after connect */
#define IDO_T22_NO_DISCONNECT_PAIR (1u << 1)  /* No disconnect pair */
#define IDO_T22_V3_HR_DATA        (1u << 2)  /* V3 HR data format */
#define IDO_T22_V3_SWIM_DATA      (1u << 3)  /* V3 Swimming data format */
#define IDO_T22_V3_ACTIVITY_DATA  (1u << 4)  /* V3 Activity data format */
#define IDO_T22_V3_GPS_DATA       (1u << 5)  /* V3 GPS format */
#define IDO_T22_DRINK_WATER_REMINDER (1u << 6)  /* Drink water reminder */

/* Table 23 — UI Set */
#define IDO_T23_LEVEL5_HR_INTERVAL   (1u << 0)  /* 5-level HR interval display */
#define IDO_T23_WALK_REMINDER        (1u << 1)  /* Walk reminder */
#define IDO_T23_BREATHE_TRAIN       (1u << 2)  /* Breathing training app */
#define IDO_T23_SCREEN_BRIGHTNESS_5_LEVEL (1u << 3)  /* 5-level screen brightness */
#define IDO_T23_ACTIVITY_SWITCH     (1u << 4)  /* Auto-detect activity toggle */
#define IDO_T23_DISTURB_HAVE_RANG_REPEAT (1u << 5)  /* DND with range/repeat */
#define IDO_T23_NIGHT_AUTO_BRIGHTNESS (1u << 6)  /* Night auto dimming */
#define IDO_T23_LONG_MTU            (1u << 7)  /* Long MTU BLE support */

/* Table 24 — Sport 5 */
#define IDO_T24_OUTDOOR_RUN    (1u << 0)  /* Outdoor run */
#define IDO_T24_INDOOR_RUN    (1u << 1)  /* Indoor run */
#define IDO_T24_OUTDOOR_CYCLE (1u << 2)  /* Outdoor cycle */
#define IDO_T24_INDOOR_CYCLE  (1u << 3)  /* Indoor cycle */
#define IDO_T24_OUTDOOR_WALK  (1u << 4)  /* Outdoor walk */
#define IDO_T24_INDOOR_WALK   (1u << 5)  /* Indoor walk */
#define IDO_T24_POOL_SWIM     (1u << 6)  /* Pool swim */
#define IDO_T24_OPEN_WATER_SWIM (1u << 7)  /* Open water swim */

/* Table 25 — Sport 6 */
#define IDO_T25_ELLIPTICAL   (1u << 0)   /* Elliptical */
#define IDO_T25_ROWER        (1u << 1)   /* Rowing machine */
#define IDO_T25_HIIT         (1u << 2)   /* HIIT training */
#define IDO_T25_CRICKET      (1u << 3)   /* Cricket */
#define IDO_T25_PILATES      (1u << 4)   /* Pilates */
#define IDO_T25_OUTDOOR_PLAY (1u << 5)   /* Outdoor play */
#define IDO_T25_OTHER_ACTIVITY (1u << 6)  /* Other activity */
#define IDO_T25_ZUMBA        (1u << 7)   /* Zumba */
#define IDO_T25_SURFING      (1u << 8)   /* Surfing */
#define IDO_T25_FOOTVOLLEY   (1u << 9)   /* Footvolley */
#define IDO_T25_STAND_WATER_SKIING (1u << 10)  /* Stand up water skiing */
#define IDO_T25_BATTLING_ROPE (1u << 11)  /* Battling ropes */

/* Table 26 — Dial Ex */
#define IDO_T26_FACTORY_RESET   (1u << 0)  /* Restore factory via app */
#define IDO_T26_LIFTING_WRIS_BACKLIGHT (1u << 1)  /* Lift wrist backlight command */
#define IDO_T26_MULTI_ACTIVITY_NO_USE_APP (1u << 2)  /* Multi-activity without app */
#define IDO_T26_MULTI_DIAL      (1u << 3)  /* Multi-dial slots */
#define IDO_T26_MEDIUM_TO_HIGH_ACTIVE_DURATION (1u << 4)  /* Medium/High active duration */
#define IDO_T26_DEFAULT_SPORT_TYPE (1u << 5)  /* Get default sport type */
#define IDO_T26_DOWNLOAD_LANGUAGE (1u << 6)  /* Download language packs */
#define IDO_T26_FLASH_LOG       (1u << 7)  /* Flash log retrieval */

/* Table 27 — Lang 4 */
#define IDO_T27_THAI                (1u << 0)   /* Thai */
#define IDO_T27_VIETNAMESE          (1u << 1)   /* Vietnamese */
#define IDO_T27_BURMESE             (1u << 2)   /* Burmese */
#define IDO_T27_FILIPINO            (1u << 3)   /* Filipino */
#define IDO_T27_TRADITIONAL_CHINESE  (1u << 4)   /* Traditional Chinese */
#define IDO_T27_GREEK               (1u << 5)   /* Greek */
#define IDO_T27_ARABIC              (1u << 6)   /* Arabic */
#define IDO_T27_SWEDEN              (1u << 7)   /* Swedish */
#define IDO_T27_FINLAND             (1u << 8)   /* Finnish */
#define IDO_T27_PERSIA              (1u << 9)   /* Persian */
#define IDO_T27_NORWEGIAN           (1u << 10)  /* Norwegian */
#define IDO_T27_MALAY               (1u << 11)  /* Malay */
#define IDO_T27_BRAZILIAN_PORTUGUESE (1u << 12)  /* Brazilian Portuguese */
#define IDO_T27_BENGALI             (1u << 13)  /* Bengali */
#define IDO_T27_KHMER               (1u << 14)  /* Khmer */

/* Table 28 — Feat Ex */
#define IDO_T28_CHARGING_TIME    (1u << 0)   /* Charging time info */
#define IDO_T28_MENU_LIST        (1u << 1)   /* Sync menu lists */
#define IDO_T28_PHOTO_WALLPAPER  (1u << 2)   /* Custom photo wallpaper */
#define IDO_T28_VOICE_TRANSMISSION (1u << 3)  /* Voice audio transmission */
#define IDO_T28_UTC_TIME_ZONE    (1u << 4)   /* UTC time zone */
#define IDO_T28_CHOICE_USE       (1u << 5)   /* 4-choose-2 logic */
#define IDO_T28_HEART_RATE_INTERVAL (1u << 6)  /* Heart rate interval limits */
#define IDO_T28_V3_SPORTS_TYPE   (1u << 7)   /* V3 sport type read/write */
#define IDO_T28_V2_SET_SHOW_MUSIC_INFO_SWITCH (1u << 8)   /* Show music info toggle */
#define IDO_T28_SUPPORT_COMPASS  (1u << 9)   /* Compass */
#define IDO_T28_SUPPORT_BAROMETRIC_ALTIMETER (1u << 10)  /* Barometric altimeter */
#define IDO_T28_SUPPORT_GET_SET_MAX_ITEMS_NUM (1u << 11)  /* Support max items limits */
#define IDO_T28_SUPPORT_V3_REPEAT_WEEK_TYPE_SETING (1u << 12)  /* V3 repeated week DND */
#define IDO_T28_SUPPORT_V2_GET_UN_DELE_MEUN (1u << 13)  /* Undeletable menu fetching */

/* Table 29 — V3 Big (64 bits: bits 0–31 and 32–63 in two words if needed) */
#define IDO_T29_V3_SYNC_ALARM   (1ULL << 0)   /* V3 sync alarms */
#define IDO_T29_UBLOX_MODEL    (1ULL << 1)   /* Ublox module */
#define IDO_T29_V3_SYNC_ACTIVITY (1ULL << 2)   /* V3 Sync activity (Custom) */
#define IDO_T29_GET_HEAT_LOG   (1ULL << 3)   /* Get overheat log */
#define IDO_T29_V3_SPO2_OFFSET_CHANGE (1ULL << 4)   /* V3 SpO2 per-minute offset */
#define IDO_T29_SCREEN_BRIGHTNESS_3_LEVEL (1ULL << 5)   /* 3-level screen brightness */
#define IDO_T29_ENCRYPTED_AUTH (1ULL << 6)   /* Encrypted authorization binding */
#define IDO_T29_V3_SLEEP       (1ULL << 7)   /* V3 sleep (Eye movement/REM) */
#define IDO_T29_ALARM_SPECIFY_TYPE (1ULL << 8)   /* Named/Categorized alarms */
#define IDO_T29_MENU_LIST_TYPE_MEASURE (1ULL << 9)   /* One-key measure menu support */
#define IDO_T29_BP_CALIBRATION_V3 (1ULL << 10)  /* V3 BP calibration */
#define IDO_T29_SWITCH_STATUS_APPEND (1ULL << 11)  /* Body power/Breath rate switch */
#define IDO_T29_HEART_RATE_MODE_V2 (1ULL << 12)  /* V2 HR mode detection */
#define IDO_T29_ALIBABA_EMAIL  (1ULL << 13)  /* Alibaba Email */
#define IDO_T29_CALENDARIO    (1ULL << 14)  /* Calendario (Google Calendar) */
#define IDO_T29_TIME_GOAL_TYPE (1ULL << 15)  /* 3-ring weekly activity goals */
#define IDO_T29_SUPPORT_HRV   (1ULL << 16)  /* HRV (Heart Rate Variability) */
#define IDO_T29_SUPPORT_UPDATE_GPS (1ULL << 17)  /* GPS offline file updates */
#define IDO_T29_SUPPORT_WARM_UP_BEFORE_RUN (1ULL << 18)  /* Pre-run warmup logic */
#define IDO_T29_SUPPORT_V3_SET_EMERGENCY_CONNECT (1ULL << 19)  /* V3 emergency (ICE) contacts */
#define IDO_T29_SUPPORT_SET_DRINK_NO_REMINDER (1ULL << 20)  /* Drink water DND period */
#define IDO_T29_SUPPORT_SET_WALK_NO_REMINDER (1ULL << 21)  /* Walk reminder DND period */
#define IDO_T29_SUPPORT_V3_REP_SCHEDULE_REMINDER (1ULL << 22)  /* V3 Schedule repeating logic */
#define IDO_T29_SUPPORT_V3_HOUR_PRECIPITATION (1ULL << 23)  /* V3 Hourly precipitation (Depr.) */
#define IDO_T29_SUPPORT_STEP_WEEK_TARGET (1ULL << 24)  /* Weekly step target */
#define IDO_T29_SUPPORT_MINI_PROGRAM (1ULL << 25)  /* Mini-program applets */
#define IDO_T29_SUPPORT_RF_GET_PERIPHERALS_INFO (1ULL << 26)  /* RF Fetch external peripherals */
#define IDO_T29_SUPPORT_RF_SET_PERIPHERALS_INFO (1ULL << 27)  /* RF Set external peripherals */
#define IDO_T29_SUPPORT_RF_SCALES_MODEL_MAP_TABLE (1ULL << 28)  /* RF Scales map table */
#define IDO_T29_SUPPORT_RF_BIND_DEVICE_TABLE (1ULL << 29)  /* RF Bind device lists */
#define IDO_T29_SUPPORT_V2_NIGHT_TURN_ON_AFTER_SUNSET (1ULL << 30)  /* Turn on backlight after sunset */
#define IDO_T29_SUPPORT_V3_SET_CONTACT_VERSION (1ULL << 31)  /* V3 Contact sync protocol 0x10 */
#define IDO_T29_SUPPORT_CALL_LIST (1ULL << 32)  /* Bluetooth Call history list */
#define IDO_T29_SUPPORT_V3_SLEEP_AVG_HR (1ULL << 33)  /* Sleep Average HR valid */
#define IDO_T29_V3_ACTIVITY_END_TIME_USE_UTC (1ULL << 34)  /* V3 Activity end timestamp UTC */
#define IDO_T29_RESET_DEVICE_BLUETOOTH (1ULL << 35)  /* Command to restart watch BLE */
#define IDO_T29_DATA_TYPE_USE_NEW_CODE (1ULL << 36)  /* File transfer uses new codes */
#define IDO_T29_SCIENTIFIC_SLEEP_SWITCH_OFF_BY_DEFAULT (1ULL << 37)  /* Sci-sleep off by default */
#define IDO_T29_HEART_RATE_OFF_BY_DEFAULT (1ULL << 38)  /* Auto-HR off by default */
#define IDO_T29_NOT_SUPPORT_SET_OVULATION (1ULL << 39)  /* Disables ovulation setting */
#define IDO_T29_NOT_SUPPORT_INDOOR_RUN_GET_VO2MAX (1ULL << 40)  /* Hides VO2 Max for Indoor Run */
#define IDO_T29_SYNC_HEALTH_SWIM_GET_AVG_FREQUENCY (1ULL << 41)  /* V3 Swim average stroke freq */
#define IDO_T29_SYNC_HEALTH_SWIM_GET_AVG_SPEED (1ULL << 42)  /* V3 Swim average speed */
#define IDO_T29_SYNC_ADD_SLEEP_AVG_SPO2 (1ULL << 43)  /* Sleep Average SpO2 valid */
#define IDO_T29_SUPPORT_DOUIV6_WATCH_DIAL_ANIMA_COMPRESS (1ULL << 44)  /* DOUIv6 Dial Animation compress */
#define IDO_T29_SYNC_ADD_SLEEP_AVG_RESPIR_RATE (1ULL << 45)  /* Sleep Average Resp rate valid */
#define IDO_T29_GET_V3_DEVICE_ALGORITHM_VERSION (1ULL << 46)  /* Get V3 Alg versions */
#define IDO_T29_SUPPORT_FASTRACK_REFLEX_WORLD (1ULL << 47)  /* Fastrack Reflex World app */
#define IDO_T29_SUPPORT_HAMA_FIT_MOVE (1ULL << 48)  /* Hama Fit Move app */
#define IDO_T29_SUPPORT_TAOBAO (1ULL << 49)  /* Taobao app */
#define IDO_T29_SUPPORT_DINGTALK (1ULL << 50)  /* DingTalk */
#define IDO_T29_SUPPORT_ALIPAY (1ULL << 51)  /* Alipay */
#define IDO_T29_SUPPORT_TOUTIAO (1ULL << 52)  /* Toutiao */
#define IDO_T29_SUPPORT_TMAIL (1ULL << 53)  /* Tmall */
#define IDO_T29_SUPPORT_JD (1ULL << 54)  /* JD.com */
#define IDO_T29_SUPPORT_PINDUODUO (1ULL << 55)  /* Pinduoduo */
#define IDO_T29_SUPPORT_BAIDU (1ULL << 56)  /* Baidu */
#define IDO_T29_SUPPORT_MEITUAN (1ULL << 57)  /* Meituan */
#define IDO_T29_SUPPORT_ELEME (1ULL << 58)  /* Ele.me */
#define IDO_T29_SUPPORT_LOUDSPEAKER (1ULL << 59)  /* Watch has a loudspeaker */
#define IDO_T29_AUTO_ACTIVITY_SWITCH_ADD_SMART_ROPE (1ULL << 60)  /* Auto-recognize smart rope */
#define IDO_T29_SUPPORT_SYNC_ACTIVITY_GET_ROPE_INFO (1ULL << 61)  /* Sync smart rope session data */
#define IDO_T29_SUPPORT_DOUYIN (1ULL << 62)  /* Douyin (Chinese TikTok) */
#define IDO_T29_SUPPORT_HOME_WEIBO (1ULL << 63)  /* Weibo */
/* Table 29 continued: bit 64 is in the next payload word (first bit). */
#define IDO_T29_SUPPORT_SET_V3_WEATHER_DYNAMIC_CONFIG_WORD2 (1u << 0)  /* V3 Weather dynamic pointers (bit 64) */

/* Table 30 — V3 Act */
#define IDO_T30_RESTORE_FACTORY   (1u << 0)  /* Restore factory */
#define IDO_T30_GET_SCREEN_BRIGHTNESS (1u << 1)  /* Get screen brightness level */
#define IDO_T30_GET_UP_HAND_GESTURE (1u << 2)  /* Get raise wrist state */
#define IDO_T30_GET_NOT_DISTURB  (1u << 3)  /* Get DND (Deprecated) */
#define IDO_T30_FAST_MSG_DATA    (1u << 4)  /* Quick SMS reply */
#define IDO_T30_GET_DEVICE_UPDATE_STATE (1u << 5)  /* Get OTA update state */
#define IDO_T30_V3_SPORTS        (1u << 6)  /* V3 Sports processing */
#define IDO_T30_V3_ACTIVITY_EXCHANGE_DATA (1u << 7)  /* V3 Live activity exchange */
#define IDO_T30_V3_BP_CALIBRATION (1u << 8)  /* V3 Blood Pressure Calibration */
#define IDO_T30_GET_SWITCH_APPEND (1u << 9)  /* Body power & Breath rate toggles */

/* Table 31 — V3 APIs */
#define IDO_T31_V3_GET_LANG_LIB   (1u << 0)   /* V3 Language library list */
#define IDO_T31_SET_PHONE_VOICE   (1u << 1)   /* Set phone volume */
#define IDO_T31_GET_WATCH_ID     (1u << 2)   /* Get watch face ID */
#define IDO_T31_HAND_WASH_REMINDER (1u << 3)   /* Hand wash reminder */
#define IDO_T31_CLEAR_BLE_CACHE  (1u << 4)   /* Clear BLE cache */
#define IDO_T31_V3_VOICE_REPLY_TXT (1u << 5)   /* V3 Voice reply to text */
#define IDO_T31_GET_DEV_NAME     (1u << 6)   /* Get device name */
#define IDO_T31_BRIGHT_SCREEN_TIME (1u << 7)   /* Bright screen time limits */
#define IDO_T31_GET_HABIT_DATA   (1u << 8)   /* Habit tracking sync */
#define IDO_T31_SIX_AXIS_SENSOR  (1u << 9)   /* 6-axis sensor for swimming */
#define IDO_T31_NO_DISTURB_ALL_DAY_ON_OFF (1u << 10)  /* DND All Day / Smart DND config */
#define IDO_T31_V2_NO_DISTURB_ALL_DAY_SWITCH (1u << 11)  /* V2 All Day DND */
#define IDO_T31_V2_NO_DISTURB_SMART_SWITCH (1u << 12)  /* V2 Smart DND */
#define IDO_T31_GET_BATTERY_MODE (1u << 13)  /* Fetch battery saver mode */
#define IDO_T31_ACTIVITY_SYNC_REAL_TIME (1u << 14)  /* V3 live activity pace */
#define IDO_T31_DATA_TRAN_OVER_WAIT_BLE (1u << 15)  /* Wait for device D1 check */
#define IDO_T31_SUPPORT_SET_HOT_START_PARAM (1u << 16)  /* Set GPS hot start params */
#define IDO_T31_SUPPORT_GET_BLE_BEEP (1u << 17)  /* Local firmware beep sounds */
#define IDO_T31_SUPPORT_SPORT_ICON_MIN_SMALL (1u << 18)  /* Sport min icon sizing (Depr.) */
#define IDO_T31_SECOND_SPORT_ICON (1u << 19)  /* 2nd tier sport icons (IDW05) */
#define IDO_T31_V3_WEATHER_ADD_SNOW_DEPTH (1u << 20)  /* V3 Weather: Snow depth */
#define IDO_T31_V3_WEATHER_ADD_SNOWFALL (1u << 21)  /* V3 Weather: Snowfall */
#define IDO_T31_V3_WEATHER_ADD_ATMOSPHERIC_PRESSURE (1u << 22)  /* V3 Weather: Atmos. pressure */
#define IDO_T31_V3_WEATHER_SEND_STRUCT_VERSION_04 (1u << 23)  /* V3 Weather protocol v04 (Moon) */
#define IDO_T31_SUPPORT_ACTIVITY_DATA_3D_DISTANCE_SPEED (1u << 24)  /* 3D Distance & Speed */
#define IDO_T31_SUPPORT_ACTIVITY_DATA_ALTITUDE_INFO (1u << 25)  /* Altitude metrics */
#define IDO_T31_SUPPORT_ACTIVITY_DATA_AVG_SLOPE (1u << 26)  /* Average slope / incline */
#define IDO_T31_SUPPORT_DAIL_COMPRESS_MODELZ4 (1u << 27)  /* LZ4 dial compression */
#define IDO_T31_SUPPORT_SYNC_ACTIVITY_GET_LOAD (1u << 28)  /* Training load index */
#define IDO_T31_SUPPORT_SYNC_ACTIVITY_GET_ANAEROBIC_TRAINING_EFFECT (1u << 29)  /* Anaerobic training effect */
#define IDO_T31_SUPPORT_SYNC_ACTIVITY_GET_RUNNING_POWER_INFO (1u << 30)  /* Running power metrics */
#define IDO_T31_SUPPORT_SYNC_ACTIVITY_GET_REAL_TIME_PHYSICAL_EXERTION (1u << 31)  /* Real-time exertion / stamina */
#define IDO_T31_SUPPORT_SYNC_ACTIVITY_GET_REAL_TIME_OXYGEN_CONSUMPTION (1ULL << 32)  /* Real-time Oxygen Cons. (VO2) */
#define IDO_T31_SUPPORT_SEND_GPS_LONGITUDE_AND_LATITUDE (1ULL << 33)  /* Fast location sync from App */
#define IDO_T31_SUPPORT_EXCHANGE_ACTIVITY_GET_ALTITUDE_RISE_LOSS (1ULL << 34)  /* Altitude ascent/descent */
#define IDO_T31_SUPPORT_EXCHANGE_ACTIVITY_GET_GPS_STATUS (1ULL << 35)  /* Exchange GPS status */

/* Table 32 — Global */
#define IDO_T32_TIKTOK   (1u << 0)   /* TikTok */
#define IDO_T32_REDBUS   (1u << 1)   /* RedBus */
#define IDO_T32_DAILYHUNT (1u << 2)  /* Dailyhunt */
#define IDO_T32_HOTSTAR  (1u << 3)   /* Hotstar */
#define IDO_T32_INSHORTS (1u << 4)   /* Inshorts */
#define IDO_T32_PAYTM    (1u << 5)   /* Paytm */
#define IDO_T32_AMAZON   (1u << 6)   /* Amazon */
#define IDO_T32_FLIPKART (1u << 7)   /* Flipkart */
#define IDO_T32_ONLY_YAHOO_EMAIL (1u << 8)    /* Yahoo Email standalone */
#define IDO_T32_ONLY_OUTLOOK_EMAIL (1u << 9)  /* Outlook standalone */
#define IDO_T32_ONLY_INSTANT_EMAIL (1u << 10) /* Instant Email standalone */
#define IDO_T32_ONLY_NHN_EMAIL (1u << 11)     /* NHN Email standalone */
#define IDO_T32_ONLY_ZOHO_EMAIL (1u << 12)    /* Zoho Email standalone */
#define IDO_T32_ONLY_EXCHANGE_EMAIL (1u << 13) /* Exchange Email standalone */
#define IDO_T32_ONLY_189_EMAIL (1u << 14)     /* 189 Email standalone */
#define IDO_T32_ONLY_GOOGLE_GMAIL (1u << 15)  /* Gmail standalone */
#define IDO_T32_VERYFIT_NOTICE (1u << 16)     /* VeryFit native notice */
#define IDO_T32_GENERAL   (1u << 17)          /* General unknown app notice */

/* Table 33 — Regions */
#define IDO_T33_PRIME    (1u << 0)   /* Amazon Prime */
#define IDO_T33_NETFLIX  (1u << 1)   /* Netflix */
#define IDO_T33_GPAY     (1u << 2)   /* Google Pay */
#define IDO_T33_PHONPE   (1u << 3)   /* PhonePe */
#define IDO_T33_SWIGGY   (1u << 4)   /* Swiggy */
#define IDO_T33_ZOMATO   (1u << 5)   /* Zomato */
#define IDO_T33_MAKE_MY_TRIP (1u << 6)  /* MakeMyTrip */
#define IDO_T33_JIO_TV   (1u << 7)   /* JioTV */
#define IDO_T33_MICROSOFT (1u << 8)  /* Microsoft */
#define IDO_T33_WHATSAPP_BUSINESS (1u << 9)   /* WhatsApp Business */
#define IDO_T33_NOISE_FIT (1u << 10) /* NoiseFit */
#define IDO_T33_MISSED_CALL (1u << 11) /* Missed Call */
#define IDO_T33_MATTERS_REMIND (1u << 12) /* Matters/To-do remind */
#define IDO_T33_YTMUSIC  (1u << 13)  /* YouTube Music */
#define IDO_T33_UBER     (1u << 14)  /* Uber */
#define IDO_T33_OLA      (1u << 15)  /* Ola */
#define IDO_T33_GOOGLE_MEET (1u << 16) /* Google Meet */
#define IDO_T33_MORMAII_SMARTWATCH (1u << 17) /* Mormaii Smartwatch */
#define IDO_T33_TECHNOS_CONNECT (1u << 18)   /* Technos Connect */
#define IDO_T33_ENJOUEI  (1u << 19)  /* Enjoei */
#define IDO_T33_ALIEXPRESS (1u << 20) /* AliExpress */
#define IDO_T33_SHOPEE   (1u << 21)  /* Shopee */
#define IDO_T33_TEAMS    (1u << 22)  /* Microsoft Teams */
#define IDO_T33_SUPPORT_99_TAXI (1u << 23)   /* 99Taxi */
#define IDO_T33_UBER_EATS (1u << 24) /* UberEats */
#define IDO_T33_IFOOD    (1u << 25)  /* iFood */
#define IDO_T33_RAPPI    (1u << 26)  /* Rappi */
#define IDO_T33_MERCADO_LIVRE (1u << 27) /* Mercado Livre */
#define IDO_T33_MAGALU   (1u << 28)  /* Magalu */
#define IDO_T33_AMERICANAS (1u << 29) /* Americanas */
#define IDO_T33_YAHOO    (1u << 30)  /* Yahoo */
#define IDO_T33_ORIENTEERING (1u << 31) /* Orienteering (Sport) */
#define IDO_T33_MOUNTAIN_BIKING (1ULL << 32)  /* Mountain biking (Sport) */
#define IDO_T33_BEACH_TENNIS (1ULL << 33)     /* Beach tennis (Sport) */
#define IDO_T33_SMART_ROPE (1ULL << 34)       /* Smart rope (Sport) */
#define IDO_T33_V2_SUPPORT_GET_ALL_CONTACT (1ULL << 35)  /* V2 Get all contacts */

/* Table 34 — Dial V3 */
#define IDO_T34_TAKING_MEDICINE (1u << 0)   /* Taking medicine */
#define IDO_T34_LOCAL_DIAL   (1u << 1)   /* Downloadable cloud dial face */
#define IDO_T34_PRESSURE_HIGH_REMINDER (1u << 2)   /* High stress reminder */
#define IDO_T34_NOT_SUPPORT_HR_HIGH_ALARM (1u << 3)   /* Disables HR high alert UI */
#define IDO_T34_SUPPORT_HR_HIGH_OR_LOW_BT_ALARM (1u << 4)   /* V3 BT HR High/Low alarm */
#define IDO_T34_SUPPORT_SEND_ORIGINAL_SIZE_D1 (1u << 5)   /* Pre-unzip file size command */
#define IDO_T34_NOT_SUPPORT_PHOTO_WALLPAPER (1u << 6)   /* Disable photo wallpaper */
#define IDO_T34_SUPPORT_CALORIE_UNIT (1u << 7)   /* Custom calorie units */
#define IDO_T34_SUPPORT_SWIM_POOL_UNIT (1u << 8)   /* Custom swimming pool units */
#define IDO_T34_V3_GET_SPORT_SORT_FIELD (1u << 9)   /* V3 max/min sport defaults */
#define IDO_T34_GET_ALEXA_DEFAULT_LANGUAGE (1u << 10)  /* Get default Alexa language */
#define IDO_T34_SET_WALLPAPER_COLOR (1u << 11)  /* V3 Set wallpaper text color */
#define IDO_T34_SUPPORT_WEAR_FLAG (1u << 12)  /* Hourly wear detection flag */
#define IDO_T34_WATCH_DIAL_SORT (1u << 13)  /* Set watch face order */
#define IDO_T34_SUPPORT_PING (1u << 14)  /* Heartbeat Ping support */
#define IDO_T34_SUPPORT_V3_BP (1u << 15)  /* V3 Blood pressure log support */
#define IDO_T34_V2_BP_SET_OR_MEASUREMENT (1u << 16)  /* V2 Blood pressure measure */
#define IDO_T34_WALLPAPER_ONLY_TIME_COLOR (1u << 17)  /* Wallpaper only allows color/pos */
#define IDO_T34_SUPPORT_BREATH_RATE (1u << 18)  /* Breathing rate tracking */
#define IDO_T34_SUPPORT_GRADE (1u << 19)  /* VO2 Level grading */
#define IDO_T34_SUPPORT_SPORT_PLAN (1u << 20)  /* Running plans & courses */
#define IDO_T34_SUPPORT_MSG_CALLING_QUICK (1u << 21)  /* SMS quick reply for calls */
#define IDO_T34_SUPPORT_MSG_ALL_SWITCH (1u << 22)  /* App notification master switch */
#define IDO_T34_SUPPORT_AIROHA_GPS_CHIP (1u << 23)  /* Airoha GPS chipset support */

/* Table 35 — Alexa */
#define IDO_T35_SCIENTIFIC_SLEEP (1u << 0)   /* Scientific Sleep (Deep/REM) */
#define IDO_T35_GET_BATTERY_LOG (1u << 1)   /* Get battery diagnostic log */
#define IDO_T35_GET_NEW_WATCH_LIST (1u << 2)   /* Get new watchface list API */
#define IDO_T35_MULTIPLE_TIMERS (1u << 3)   /* Support multiple active timers */
#define IDO_T35_GET_MENU_LIST (1u << 4)   /* Fetch dynamic menu lists */
#define IDO_T35_AUTO_SYNC_V3_HEALTH_DATA (1u << 5)   /* Auto sync health every 30m */
#define IDO_T35_GET_DEVICE_LOG_STATE (1u << 6)   /* Device reboot log flag */
#define IDO_T35_DATA_TRAN_CONTINUE (1u << 7)   /* Breakpoint resume transfer */
#define IDO_T35_NOTIFY_ICON_ADAPTIVE (1u << 8)   /* Adaptive notification icons */
#define IDO_T35_SET_SCIENTIFIC_SLEEP_SWITCH (1u << 9)   /* On/off switch for Sci-Sleep */
#define IDO_T35_PRESSURE_NOTIFY_FLAG_MODE (1u << 10)  /* Stress all-day notification */
#define IDO_T35_SPO2_NOTIFY_FLAG (1u << 11)  /* SpO2 auto notification flag */
#define IDO_T35_MENSTRUAL_NOTIFY_FLAG (1u << 12)  /* Menstrual cycle notification flag */
#define IDO_T35_DRINK_WATER_NOTIFY_FLAG (1u << 13)  /* Drink water notification flag */
#define IDO_T35_GET_HEALTH_SWITCH_STATE (1u << 14)  /* Fetch all health switch states */
#define IDO_T35_SET_TEMPERATURE_SWITCH (1u << 15)  /* Night body temp switch */
#define IDO_T35_FIND_PHONE_STOP (1u << 16)  /* Stop find phone command */
#define IDO_T35_PERMISSIONS_STATE (1u << 17)  /* Send app permission state to ble */
#define IDO_T35_SUPPORT_ADD_NIGHT_LEVEL (1u << 18)  /* Add night level screen bright */
#define IDO_T35_SUPPORT_SMART_COMPETITOR (1u << 19)  /* Smart pacing/competitor */
#define IDO_T35_SUPPORT_SET_MENSTRUAL_ON_OFF (1u << 20)  /* Set Menstrual switch */
#define IDO_T35_SUPPORT_SET_VOICE_ASSISTANT_STATUS (1u << 21)  /* Set voice assistant status */

/* Table 36 — AI Ex */
#define IDO_T36_ALEXA_SET_WEATHER (1u << 0)   /* Alexa Set Weather */
#define IDO_T36_ALEXA_JUMP_SPORT_UI (1u << 1)   /* Alexa jump to sport UI */
#define IDO_T36_ALEXA_JUMP_UI (1u << 2)   /* Alexa jump to general UI */
#define IDO_T36_ALEXA_EASY_OPERATE (1u << 3)   /* Alexa Easy Control */
#define IDO_T36_ALEXA_GET_ALARM (1u << 4)   /* Alexa Get Alarms */
#define IDO_T36_ALEXA_SET_ON_OFF (1u << 5)   /* Alexa app command switch */
#define IDO_T36_GET_WALK_REMINDER (1u << 6)   /* Fetch walk reminder goals */
#define IDO_T36_SET_MUSIC_NAME (1u << 7)   /* Set music track name */
#define IDO_T36_LONG_CITY_NAME (1u << 8)   /* Long city name strings */
#define IDO_T36_MAX_BLOOD_OXYGEN (1u << 9)   /* Max Oxygen (VO2) algorithm */
#define IDO_T36_SYSTEM_TAKE_PICTURES (1u << 10)  /* System native camera support */
#define IDO_T36_WALK_TIME_REMINDER (1u << 11)  /* Live walking reminder */
#define IDO_T36_GET_HEART_RATE_REMINDER (1u << 12)  /* Get High/Low HR threshold */
#define IDO_T36_STEPS_ONE_MINUTE (1u << 13)  /* 1-minute step interval */
#define IDO_T36_SHOW_DETECTION_TIME (1u << 14)  /* Show detection time on UI */
#define IDO_T36_TIME_ZONE_FLOAT (1u << 15)  /* Decimals in timezone (x100) */
#define IDO_T36_SET_ALARM_SPECIFY_TYPE (1u << 16)  /* V3 Alarm specific names */
#define IDO_T36_V3_BODY_POWER (1u << 17)  /* V3 Body Battery (Power) */
#define IDO_T36_SUPPORT_SET_V3_ADD_48_HOUR_WEATHER_DATA (1u << 18)  /* V3 48-Hour Weather Forecast */
#define IDO_T36_AI_WATCH_DIAL (1u << 19)  /* AI Watch Dials */
#define IDO_T36_AI_VOICE (1u << 20)  /* AI Voice System */

/* Table 37 — Config */
#define IDO_T37_SUPPORT_CYCLING_UNIT (1u << 0)   /* Distinct cycling units */
#define IDO_T37_SUPPORT_WALK_RUN_UNIT (1u << 1)   /* Distinct walk/run units */
#define IDO_T37_MID_HIGH_TIME_GOAL (1u << 2)   /* Mid/High intensity targets */
#define IDO_T37_WALK_REMINDER_TIME_GOAL (1u << 3)   /* Walk reminder time targets */
#define IDO_T37_EXCHANGE_DATA_REAL_TIME_PACE (1u << 4)   /* Real-time pace via exchange */
#define IDO_T37_SUPPORT_PAIR_EACH_CONNECT (1u << 5)   /* System pair without clear */
#define IDO_T37_SUPPORT_APP_SEND_VOICE_TO_BLE (1u << 6)   /* Send compressed SBC audio */
#define IDO_T37_SET_SPO2_LOW_VALUE (1u << 7)   /* SpO2 Low threshold setting */
#define IDO_T37_SPO2_ALL_DAY_ON_OFF (1u << 8)   /* All-day SpO2 monitoring */
#define IDO_T37_SMART_HEART_RATE (1u << 9)   /* Smart HR tracking */
#define IDO_T37_ALEXA_REMINDER_ADD_SECOND (1u << 10)  /* Alexa reminder supports seconds */
#define IDO_T37_SYNC_NOISE (1u << 11)  /* Noise/Decibel syncing */
#define IDO_T37_SYNC_TEMPERATURE (1u << 12)  /* Body Temp syncing */
#define IDO_T37_SET_100_SPORT_SORT (1u << 13)  /* 100+ sport order sorting */
#define IDO_T37_SPORT_MEDIUM_ICON (1u << 14)  /* 100+ sport medium icons */
#define IDO_T37_SET_20_SPORT_PARAM_SORT (1u << 15)  /* Sort 20 sport metrics */
#define IDO_T37_SET_MAIN_UI_SORT (1u << 16)  /* Rearrange watch main widgets */
#define IDO_T37_SCHEDULE_REMINDER (1u << 17)  /* Schedule / To-do reminders */
#define IDO_T37_AUTO_ACTIVITY_SWITCH (1u << 18)  /* Auto recognize sport toggle */
#define IDO_T37_GET_CALORIE_DISTANCE_GOAL (1u << 19)  /* Fetch Cal/Distance targets */
#define IDO_T37_SET_STRESS_CALIBRATION (1u << 20)  /* Set Stress tracking calibration */
#define IDO_T37_WATCH_CAPACITY_SIZE_DISPLAY (1u << 21)  /* Display watch storage size */
#define IDO_T37_WATCH_PHOTO_POSITION_MOVE (1u << 22)  /* Move clock on photo face */
#define IDO_T37_CHOOSE_OTHER_OTA_MODE (1u << 23)  /* Select custom OTA mode */
#define IDO_T37_SUPPORT_NEW_RETAIN_DATA (1u << 24)  /* Delete app without wiping watch */
#define IDO_T37_SUPPORT_WALK_GOAL_STEPS (1u << 25)  /* Walk goal steps per hour */
#define IDO_T37_NEW_RETAIN_DATA (1u << 26)  /* Unbind retains watch data */

/* Table 38 — UI Ctrl */
#define IDO_T38_WALK_REMINDER_ADD_NOTIFY (1u << 0)   /* Walk reminder notify type */
#define IDO_T38_SET_FITNESS_GUIDANCE (1u << 1)   /* Fitness guidance toggle */
#define IDO_T38_SYNC_CONTACT (1u << 2)   /* Sync Contacts list */
#define IDO_T38_SET_WEATHER_SUN_TIME (1u << 3)   /* Weather includes sunrise/set */
#define IDO_T38_SET_V3_WEATHER (1u << 4)   /* V3 Weather protocol */
#define IDO_T38_SET_V3_WEATHER_SUNRISE (1u << 5)   /* V3 Weather 3-day sunrise */
#define IDO_T38_SET_V3_WEATHER_ADD_AIR_GRADE (1u << 6)   /* V3 Weather Air quality */
#define IDO_T38_SET_V3_WORLD_TIME (1u << 7)   /* V3 World Time setup */
#define IDO_T38_SET_NOTIFY_ADD_APP_NAME (1u << 8)   /* App names in 8 languages */
#define IDO_T38_TRANSFER_MUSIC_FILE (1u << 9)   /* Transfer music to watch */
#define IDO_T38_GET_ACTIVITY_SWITCH (1u << 10)  /* Fetch auto-sport recognition */
#define IDO_T38_HISTORY_MENSTRUAL (1u << 11)  /* Historical Menstrual data */
#define IDO_T38_BLE_AND_BT_VERSION (1u << 12)  /* Get BLE and BT triple versions */
#define IDO_T38_MUSIC_ADD_SINGER_NAME (1u << 13)  /* Display Singer Name */
#define IDO_T38_MENSTRUAL_ADD_PREGNANCY (1u << 14)  /* Add pregnancy to cycle */
#define IDO_T38_ALEXA_CONTROLL_100_SPORTS (1u << 15)  /* Alexa handles 100 sports */
#define IDO_T38_WALK_TIME_REMINDER_DEPRECATED (1u << 16)  /* Deprecated attribute */
#define IDO_T38_SET_UNREAD_APP_REMINDER (1u << 17)  /* Unread app red dot toggle */
#define IDO_T38_ALEXA_CONTROLL_100_BRIGHTNESS (1u << 18)  /* Alexa 1-100% Brightness */
#define IDO_T38_GET_BLE_MAC_ADDR (1u << 19)  /* Fetch BT Mac Address */
#define IDO_T38_SET_NOTIFICATION_STATUS (1u << 20)  /* Notification app switch config */
#define IDO_T38_SYNC_V3_ACTIVITY_ADD_PARAM (1u << 21)  /* V3 Activity Extra Params */
#define IDO_T38_STRESS_CALIBRATION_THRESHOLD (1u << 22)  /* Stress Threshold Calibration */
#define IDO_T38_NOT_SUPPORT_CALLING_3S_DELAY (1u << 23)  /* Hide 3-sec call delay toggle */
#define IDO_T38_UI_CONTROLL_SPORTS (1u << 24)  /* Alexa UI controls sports fields */
#define IDO_T38_V2_SET_UNREAD_APP_REMINDER (1u << 25)  /* V2 Unread App Red Dot */
#define IDO_T38_SUPPORT_SET_FAST_MODE_WHEN_SYNC_CONFIG (1u << 26)  /* Fast mode boot sync */
#define IDO_T38_SUPPORT_ACTIVITY_SWITCH_ADD_BICYCLE (1u << 27)  /* Auto-recognize Bicycle */
#define IDO_T38_SUPPORT_V3_HEALTH_SLEEP_DATA_TYPE_NOT_LIMIT (1u << 28)  /* V3 sleep types unlimited */
#define IDO_T38_SUPPORT_DIAL_FRAME_ENCODE_FORMAT_ARGB6666 (1u << 29)  /* Dial uses argb6666 format */
#define IDO_T38_SUPPORT_DEVICE_CONTROL_FAST_MODE_ALONE (1u << 30)  /* Watch auto fast/slow mode */
#define IDO_T38_SUPPORT_APP_SEND_PHONE_SYSTEM_INFO (1u << 31)  /* App sends OS info (iOS/Andr) */
#define IDO_T38_SUPPORT_ONEKEY_DOUBLE_CONTACT (1ULL << 32)  /* Dual BT/BLE 1-tap connect */
#define IDO_T38_SUPPORT_DIAL_FRAME_ENCODE_WIDTH_USE_EVEN_NUMBER_ALIGNING (1ULL << 33)  /* Even-number dial width align */

/* Table 39 — Toggles */
#define IDO_T39_AUTO_ACTIVITY_PAUSE_SWITCH_NOT_DISPLAY (1u << 0)   /* Hide Auto-Pause switch UI */
#define IDO_T39_AUTO_ACTIVITY_END_SWITCH_NOT_DISPLAY (1u << 1)   /* Hide Auto-End switch UI */
#define IDO_T39_AUTO_ACTIVITY_SET_GET_USE_NEW_STRUCT_EXCHANGE (1u << 2)   /* New Auto-Activity structure */
#define IDO_T39_NOT_SUPPORT_DELETE_ADD_SPORT_SORT (1u << 3)   /* Disable Sport add/delete (sort only) */
#define IDO_T39_SUPPORT_GET_SN_INFO (1u << 4)   /* Fetch SN Info */
#define IDO_T39_SUPPORT_SET_ALEXA_FUNCTION_ON_OFF (1u << 5)   /* Alexa kill switch */
#define IDO_T39_SUPPORT_SET_HISTORICAL_MENSTRUATION_USE_V2 (1u << 6)   /* Menstrual V2 Historical */
#define IDO_T39_SUPPORT_TITAN_SMART_WORLD (1u << 7)   /* Titan Smart World */
#define IDO_T39_NOT_SUPPORT_APP_SEND_RUN_PLAN (1u << 8)   /* Block App Run Plan sending */
#define IDO_T39_SUPPORT_SET_NOTICE_MESSAGE_STATE_USE_VERSION_0x20 (1u << 9)   /* Set Notice Message V0x20 */
#define IDO_T39_SUPPORT_GET_UNIT (1u << 10)  /* Retrieve units */
#define IDO_T39_SUPPORT_SET_CALL_QUICK_REPLY_ON_OFF (1u << 11)  /* SMS Quick Reply Toggle */
#define IDO_T39_SUPPORT_RYZE_CONNECT (1u << 12)  /* Ryze Connect App */
#define IDO_T39_SUPPORT_LOOPS_FIT (1u << 13)  /* LOOPS FIT App */
#define IDO_T39_SUPPORT_TAS_SMART (1u << 14)  /* TAS Smart App */
#define IDO_T39_SUPPORT_BP_MODEL_FILE_UPDATE (1u << 15)  /* Blood Pressure model updates */
#define IDO_T39_SUPPORT_GAME_TIME_REMINDER (1u << 16)  /* App Game time limits */
#define IDO_T39_SUPPORT_ACTIVITY_TYPE_TREADMILLS_SHOW_STEP (1u << 17)  /* Treadmill UI shows steps */
#define IDO_T39_SUPPORT_ACHIEVED_REMIND_ON_OFF (1u << 18)  /* Goal Achieved Toggle */
#define IDO_T39_SUPPORT_DRINK_PLAN (1u << 19)  /* Smart Drink Water Plan */
#define IDO_T39_SUPPORT_SLEEP_PLAN (1u << 20)  /* Smart Sleep Plan */
#define IDO_T39_SUPPORT_SPORT_GET_AUTO_PAUSE_END (1u << 21)  /* Fetch auto-pause limits */
#define IDO_T39_SUPPORT_SET_NOISE_NOTIFY (1u << 22)  /* Noise (Decibel) alerts */
#define IDO_T39_SUPPORT_SET_NOISE_OVERWARNING (1u << 23)  /* Noise Warning thresholds */
#define IDO_T39_SUPPORT_OPERATE_APPLIST_WALLPAPER (1u << 24)  /* Sync App-list Wallpaper */
#define IDO_T39_SUPPORT_V3_SPORT_RECORD_SHOW_CONFIG (1u << 25)  /* V3 Sport display config */

/* Table 40 — Banks */
#define IDO_T40_SUPPORT_ITAU (1u << 0)   /* Itaú Bank */
#define IDO_T40_SUPPORT_BANCO_DO_BRASIL (1u << 1)   /* Banco do Brasil */
#define IDO_T40_SUPPORT_CORREIOS (1u << 2)   /* Correios */
#define IDO_T40_SUPPORT_BANCO_INTER (1u << 3)   /* Banco Inter */
#define IDO_T40_SUPPORT_CAIXA_ECONOMICA (1u << 4)   /* Caixa Econômica */

/* Table 41 — Apps */
#define IDO_T41_SUPPORT_NEON (1u << 0)   /* Neon */
#define IDO_T41_SUPPORT_SANTANDER (1u << 1)   /* Santander */
#define IDO_T41_SUPPORT_NEXT (1u << 2)   /* Next */
#define IDO_T41_SUPPORT_SHEIN (1u << 3)   /* Shein */
#define IDO_T41_SUPPORT_GOOGLE_TASK (1u << 4)   /* Google Task */
#define IDO_T41_SUPPORT_MICROSOFT_TO_DO (1u << 5)   /* Microsoft To Do */
#define IDO_T41_SUPPORT_TICKTICK (1u << 6)   /* TickTick */
#define IDO_T41_SUPPORT_TODOIST (1u << 7)   /* Todoist */

/* Table 42 — Ex Apps */
#define IDO_T42_SUPPORT_FACEBOOK_MESSENGER (1u << 0)   /* Facebook Messenger */
#define IDO_T42_SUPPORT_NUBANK (1u << 1)   /* Nubank */
#define IDO_T42_SUPPORT_BRADESCO (1u << 2)   /* Bradesco */
#define IDO_T42_SUPPORT_PRIME_VIDEO (1u << 3)   /* Prime Video */
#define IDO_T42_SUPPORT_PHOTO_PREVIEW_FUNCTION (1u << 4)   /* Watch photo preview */
#define IDO_T42_SUPPORT_FAST_CALLING_QUICK_VF (1u << 5)   /* Fast Calling VeryFit app */
#define IDO_T42_SUPPORT_HISTORICAL_MENSTRUATION_EXCHANGE (1u << 6)   /* Historical Menstrual V3 */
#define IDO_T42_SUPPORT_PROTOCOL_V3_MENSTRUATION_CONFIG (1u << 7)   /* Menstrual Config V3 */
#define IDO_T42_SUPPORT_FAMILY_CARE_REMINDER (1u << 8)   /* Family Care reminder */
#define IDO_T42_SUPPORT_CRICKET_NOT_DISPLAY_STEP_COUNT (1u << 9)   /* Hide steps in Cricket mode */
#define IDO_T42_SUPPORT_ALIPAY_AUTH (1u << 10)  /* Alipay Auth binding */
#define IDO_T42_SUPPORT_SPORT_AVERAGE_SPEED_NOT_DISPLAY (1u << 11)  /* Hide Avg Speed on certain modes */
#define IDO_T42_SUPPORT_PROTOCOL_V3_MENU_LIST (1u << 12)  /* Menu lists Protocol V3 */

#ifdef __cplusplus
}
#endif

#endif /* IDO_FUNC_TABLES_H */
