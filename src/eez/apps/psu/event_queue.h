/*
 * EEZ PSU Firmware
 * Copyright (C) 2016-present, Envox d.o.o.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

namespace eez {
namespace psu {
namespace event_queue {

static const int EVENT_TYPE_NONE = 0;
static const int EVENT_TYPE_INFO = 1;
static const int EVENT_TYPE_WARNING = 2;
static const int EVENT_TYPE_ERROR = 3;

////////////////////////////////////////////////////////////////////////////////

#define LIST_OF_EVENTS                                                                             \
    EVENT_SCPI_ERROR(SCPI_ERROR_AUX_TEMP_SENSOR_TEST_FAILED, "AUX temp failed")                    \
    EVENT_SCPI_ERROR(SCPI_ERROR_CH1_TEMP_SENSOR_TEST_FAILED, "CH1 temp failed")                    \
    EVENT_SCPI_ERROR(SCPI_ERROR_CH2_TEMP_SENSOR_TEST_FAILED, "CH2 temp failed")                    \
    EVENT_SCPI_ERROR(SCPI_ERROR_CH3_TEMP_SENSOR_TEST_FAILED, "CH3 temp failed")                    \
    EVENT_SCPI_ERROR(SCPI_ERROR_CH1_DOWN_PROGRAMMER_SWITCHED_OFF, "DProg CH1 disabled")            \
    EVENT_SCPI_ERROR(SCPI_ERROR_CH2_DOWN_PROGRAMMER_SWITCHED_OFF, "DProg CH2 disabled")            \
    EVENT_SCPI_ERROR(SCPI_ERROR_CH3_DOWN_PROGRAMMER_SWITCHED_OFF, "DProg CH3 disabled")            \
    EVENT_SCPI_ERROR(SCPI_ERROR_CH1_OUTPUT_FAULT_DETECTED, "CH1 output fault")                     \
    EVENT_SCPI_ERROR(SCPI_ERROR_CH2_OUTPUT_FAULT_DETECTED, "CH2 output fault")                     \
    EVENT_SCPI_ERROR(SCPI_ERROR_CH3_OUTPUT_FAULT_DETECTED, "CH3 output fault")                     \
    EVENT_ERROR(CH1_OVP_TRIPPED, 0, "Ch1 OVP tripped")                                             \
    EVENT_ERROR(CH2_OVP_TRIPPED, 1, "Ch2 OVP tripped")                                             \
    EVENT_ERROR(CH3_OVP_TRIPPED, 2, "Ch3 OVP tripped")                                             \
    EVENT_ERROR(CH1_OCP_TRIPPED, 10, "Ch1 OCP tripped")                                             \
    EVENT_ERROR(CH2_OCP_TRIPPED, 11, "Ch2 OCP tripped")                                             \
    EVENT_ERROR(CH3_OCP_TRIPPED, 12, "Ch3 OCP tripped")                                             \
    EVENT_ERROR(CH1_OPP_TRIPPED, 20, "Ch1 OPP tripped")                                             \
    EVENT_ERROR(CH2_OPP_TRIPPED, 21, "Ch2 OPP tripped")                                             \
    EVENT_ERROR(CH3_OPP_TRIPPED, 22, "Ch3 OPP tripped")                                             \
    EVENT_ERROR(FILE_UPLOAD_FAILED, 30, "File upload failed")                                       \
    EVENT_ERROR(FILE_DOWNLOAD_FAILED, 31, "File download failed")                                  \
    EVENT_ERROR(CH1_IOEXP_RESET_DETECTED, 40, "Ch1 IOEXP reset detected")                          \
    EVENT_ERROR(CH2_IOEXP_RESET_DETECTED, 41, "Ch2 IOEXP reset detected")                          \
    EVENT_ERROR(CH3_IOEXP_RESET_DETECTED, 42, "Ch3 IOEXP reset detected")                          \
    EVENT_ERROR(CH1_IOEXP_FAULT_MATCH_DETECTED, 50, "Ch1 IOEXP fault match detected")              \
    EVENT_ERROR(CH2_IOEXP_FAULT_MATCH_DETECTED, 51, "Ch2 IOEXP fault match detected")              \
    EVENT_ERROR(CH3_IOEXP_FAULT_MATCH_DETECTED, 52, "Ch3 IOEXP fault match detected")              \
    EVENT_ERROR(AUX_OTP_TRIPPED, 60, "AUX OTP tripped")                                            \
    EVENT_ERROR(CH1_OTP_TRIPPED, 70, "CH1 OTP tripped")                                            \
    EVENT_ERROR(CH2_OTP_TRIPPED, 71, "CH2 OTP tripped")                                            \
    EVENT_ERROR(CH3_OTP_TRIPPED, 72, "CH3 OTP tripped")                                            \
    EVENT_ERROR(CH1_REMOTE_SENSE_REVERSE_POLARITY_DETECTED, 80, "CH1 rsense reverse polarity detected") \
    EVENT_ERROR(CH2_REMOTE_SENSE_REVERSE_POLARITY_DETECTED, 81, "CH2 rsense reverse polarity detected") \
    EVENT_ERROR(CH3_REMOTE_SENSE_REVERSE_POLARITY_DETECTED, 82, "CH3 rsense reverse polarity detected") \
    EVENT_WARNING(CH1_CALIBRATION_DISABLED, 0, "Ch1 calibration disabled")                         \
    EVENT_WARNING(CH2_CALIBRATION_DISABLED, 1, "Ch2 calibration disabled")                         \
    EVENT_WARNING(CH3_CALIBRATION_DISABLED, 2, "Ch3 calibration disabled")                         \
    EVENT_WARNING(CH1_UNKNOWN_PWRGOOD_STATE, 10, "Ch1 unknown PWRGOOD")                             \
    EVENT_WARNING(CH2_UNKNOWN_PWRGOOD_STATE, 11, "Ch2 unknown PWRGOOD")                             \
    EVENT_WARNING(CH3_UNKNOWN_PWRGOOD_STATE, 12, "Ch3 unknown PWRGOOD")                             \
    EVENT_WARNING(ETHERNET_NOT_CONNECTED, 20, "Ethernet not connected")                            \
    EVENT_WARNING(AUTO_RECALL_VALUES_MISMATCH, 21, "Auto-recall mismatch")                         \
    EVENT_WARNING(NTP_REFRESH_FAILED, 22, "NTP refresh failed")                                    \
    EVENT_WARNING(FILE_UPLOAD_ABORTED, 23, "File upload aborted")                                  \
    EVENT_WARNING(FILE_DOWNLOAD_ABORTED, 24, "File download aborted")                              \
    EVENT_INFO(WELCOME, 0, "Welcome!")                                                             \
    EVENT_INFO(POWER_UP, 1, "Power up")                                                            \
    EVENT_INFO(POWER_DOWN, 2, "Power down")                                                        \
    EVENT_INFO(CALIBRATION_PASSWORD_CHANGED, 3, "Calibration password changed")                    \
    EVENT_INFO(SOUND_ENABLED, 4, "Sound enabled")                                                  \
    EVENT_INFO(SOUND_DISABLED, 5, "Sound disabled")                                                \
    EVENT_INFO(SYSTEM_DATE_TIME_CHANGED, 6, "Date/time changed")                                   \
    EVENT_INFO(ETHERNET_ENABLED, 7, "Ethernet enabled")                                            \
    EVENT_INFO(ETHERNET_DISABLED, 8, "Ethernet disabled")                                          \
    EVENT_INFO(SYSTEM_PASSWORD_CHANGED, 9, "System password changed")                              \
    EVENT_INFO(CH1_OUTPUT_ENABLED, 10, "Ch1 output on")                                            \
    EVENT_INFO(CH2_OUTPUT_ENABLED, 11, "Ch2 output on")                                            \
    EVENT_INFO(CH3_OUTPUT_ENABLED, 12, "Ch3 output on")                                            \
    EVENT_INFO(SYSTEM_DATE_TIME_CHANGED_DST, 20, "Date/time changed (DST)")                        \
    EVENT_INFO(CH1_OUTPUT_DISABLED, 30, "Ch1 output off")                                          \
    EVENT_INFO(CH2_OUTPUT_DISABLED, 31, "Ch2 output off")                                          \
    EVENT_INFO(CH3_OUTPUT_DISABLED, 32, "Ch3 output off")                                          \
    EVENT_INFO(CH1_REMOTE_SENSE_ENABLED, 40, "Ch1 remote sense enabled")                           \
    EVENT_INFO(CH2_REMOTE_SENSE_ENABLED, 41, "Ch2 remote sense enabled")                           \
    EVENT_INFO(CH3_REMOTE_SENSE_ENABLED, 42, "Ch3 remote sense enabled")                           \
    EVENT_INFO(CH1_REMOTE_SENSE_DISABLED, 50, "Ch1 remote sense disabled")                         \
    EVENT_INFO(CH2_REMOTE_SENSE_DISABLED, 51, "Ch2 remote sense disabled")                         \
    EVENT_INFO(CH3_REMOTE_SENSE_DISABLED, 52, "Ch3 remote sense disabled")                         \
    EVENT_INFO(CH1_REMOTE_PROG_ENABLED, 60, "Ch1 remote prog enabled")                             \
    EVENT_INFO(CH2_REMOTE_PROG_ENABLED, 61, "Ch2 remote prog enabled")                             \
    EVENT_INFO(CH3_REMOTE_PROG_ENABLED, 62, "Ch3 remote prog enabled")                             \
    EVENT_INFO(CH1_REMOTE_PROG_DISABLED, 70, "Ch1 remote prog disabled")                           \
    EVENT_INFO(CH2_REMOTE_PROG_DISABLED, 71, "Ch2 remote prog disabled")                           \
    EVENT_INFO(CH3_REMOTE_PROG_DISABLED, 72, "Ch3 remote prog disabled")                           \
    EVENT_INFO(RECALL_FROM_PROFILE_0, 80, "Recall from profile 0")                                 \
    EVENT_INFO(RECALL_FROM_PROFILE_1, 81, "Recall from profile 1")                                 \
    EVENT_INFO(RECALL_FROM_PROFILE_2, 82, "Recall from profile 2")                                 \
    EVENT_INFO(RECALL_FROM_PROFILE_3, 83, "Recall from profile 3")                                 \
    EVENT_INFO(RECALL_FROM_PROFILE_4, 84, "Recall from profile 4")                                 \
    EVENT_INFO(RECALL_FROM_PROFILE_5, 85, "Recall from profile 5")                                 \
    EVENT_INFO(RECALL_FROM_PROFILE_6, 86, "Recall from profile 6")                                 \
    EVENT_INFO(RECALL_FROM_PROFILE_7, 87, "Recall from profile 7")                                 \
    EVENT_INFO(RECALL_FROM_PROFILE_8, 88, "Recall from profile 8")                                 \
    EVENT_INFO(RECALL_FROM_PROFILE_9, 89, "Recall from profile 9")                                 \
    EVENT_INFO(DEFAULE_PROFILE_CHANGED_TO_0, 90, "Default profile changed to 0")                   \
    EVENT_INFO(DEFAULE_PROFILE_CHANGED_TO_1, 91, "Default profile changed to 1")                   \
    EVENT_INFO(DEFAULE_PROFILE_CHANGED_TO_2, 92, "Default profile changed to 2")                   \
    EVENT_INFO(DEFAULE_PROFILE_CHANGED_TO_3, 93, "Default profile changed to 3")                   \
    EVENT_INFO(DEFAULE_PROFILE_CHANGED_TO_4, 94, "Default profile changed to 4")                   \
    EVENT_INFO(DEFAULE_PROFILE_CHANGED_TO_5, 95, "Default profile changed to 5")                   \
    EVENT_INFO(DEFAULE_PROFILE_CHANGED_TO_6, 96, "Default profile changed to 6")                   \
    EVENT_INFO(DEFAULE_PROFILE_CHANGED_TO_7, 97, "Default profile changed to 7")                   \
    EVENT_INFO(DEFAULE_PROFILE_CHANGED_TO_8, 98, "Default profile changed to 8")                   \
    EVENT_INFO(DEFAULE_PROFILE_CHANGED_TO_9, 99, "Default profile changed to 9")                   \
    EVENT_INFO(CH1_CALIBRATION_ENABLED, 100, "Ch1 calibration enabled")                            \
    EVENT_INFO(CH2_CALIBRATION_ENABLED, 101, "Ch2 calibration enabled")                            \
    EVENT_INFO(CH3_CALIBRATION_ENABLED, 102, "Ch3 calibration enabled")                            \
    EVENT_INFO(COUPLED_IN_PARALLEL, 110, "Coupled in parallel")                                    \
    EVENT_INFO(COUPLED_IN_SERIES, 111, "Coupled in series")                                        \
    EVENT_INFO(CHANNELS_UNCOUPLED, 112, "Channels uncoupled")                                      \
    EVENT_INFO(CHANNELS_TRACKED, 113, "Channels operates in track mode")                           \
    EVENT_INFO(OUTPUT_PROTECTION_COUPLED, 114, "Output protection coupled")                        \
    EVENT_INFO(OUTPUT_PROTECTION_DECOUPLED, 115, "Output protection decoupled")                    \
    EVENT_INFO(SHUTDOWN_WHEN_PROTECTION_TRIPPED_ENABLED, 116, "Shutdown when tripped enabled")     \
    EVENT_INFO(SHUTDOWN_WHEN_PROTECTION_TRIPPED_DISABLED, 117, "Shutdown when tripped disabled")   \
    EVENT_INFO(FORCE_DISABLING_ALL_OUTPUTS_ON_POWERUP_ENABLED, 118, "Force disabling outputs enabled") \
    EVENT_INFO(FORCE_DISABLING_ALL_OUTPUTS_ON_POWERUP_DISABLED, 119, "Force disabling outputs disabled") \
    EVENT_INFO(FRONT_PANEL_LOCKED, 120, "Front panel locked")                                      \
    EVENT_INFO(FRONT_PANEL_UNLOCKED, 121, "Front panel unlocked")                                  \
    EVENT_INFO(RECALL_FROM_FILE, 122, "Recall from file")                                          \
    EVENT_INFO(FILE_UPLOAD_SUCCEEDED, 123, "File upload succeeded")                                \
    EVENT_INFO(FILE_DOWNLOAD_SUCCEEDED, 124, "File download succeeded")                            \
    EVENT_INFO(COUPLED_IN_COMMON_GROUND, 125, "Coupled in common ground")                          \
    EVENT_INFO(COUPLED_IN_SPLIT_RAIL, 126, "Coupled in split rail")

#define EVENT_ERROR_START_ID 10000
#define EVENT_WARNING_START_ID 12000
#define EVENT_INFO_START_ID 14000

#define EVENT_SCPI_ERROR(ID, TEXT)
#define EVENT_ERROR(NAME, ID, TEXT) EVENT_ERROR_##NAME = EVENT_ERROR_START_ID + ID,
#define EVENT_WARNING(NAME, ID, TEXT) EVENT_WARNING_##NAME = EVENT_WARNING_START_ID + ID,
#define EVENT_INFO(NAME, ID, TEXT) EVENT_INFO_##NAME = EVENT_INFO_START_ID + ID,
enum Events { LIST_OF_EVENTS };
#undef EVENT_SCPI_ERROR
#undef EVENT_INFO
#undef EVENT_WARNING
#undef EVENT_ERROR

////////////////////////////////////////////////////////////////////////////////

static const int EVENTS_PER_PAGE = 8;

////////////////////////////////////////////////////////////////////////////////

struct EventQueueHeader {
    uint32_t magicNumber;
    uint16_t version;
    uint16_t head;
    uint16_t size;
    uint16_t lastErrorEventIndex;
};

struct Event {
    uint32_t dateTime;
    int16_t eventId;
};

void init();
void tick(uint32_t tick_usec);

void getLastErrorEvent(Event *e);

int getEventType(Event *e);
const char *getEventMessage(Event *e);

void pushEvent(int16_t eventId);

void markAsRead();

int getNumPages();
int getActivePageNumEvents();
void getActivePageEvent(int i, Event *e);
void moveToFirstPage();
void moveToNextPage();
void moveToPreviousPage();
int getActivePageIndex();

} // namespace event_queue
} // namespace psu
} // namespace eez
