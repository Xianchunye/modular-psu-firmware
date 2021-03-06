/*
 * EEZ Modular Firmware
 * Copyright (C) 2015-present, Envox d.o.o.
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

#include <eez/modules/psu/psu.h>

#include <eez/modules/psu/calibration.h>
#include <eez/modules/psu/channel_dispatcher.h>
#include <eez/modules/psu/profile.h>
#include <eez/modules/psu/scpi/psu.h>
#include <eez/modules/psu/trigger.h>

namespace eez {
namespace psu {
namespace scpi {

////////////////////////////////////////////////////////////////////////////////

scpi_result_t scpi_cmd_outputModeQ(scpi_t *context) {
    Channel *channel = param_channel(context);
    if (!channel) {
        return SCPI_RES_ERR;
    }

    SCPI_ResultText(context, channel->getModeStr());

    return SCPI_RES_OK;
}

scpi_result_t scpi_cmd_outputProtectionClear(scpi_t *context) {
    uint32_t channels = param_channels(context);
    if (channels == 0) {
        return SCPI_RES_ERR;
    }

    for (int channelIndex = 0; channelIndex < CH_NUM; channelIndex++) {
        if ((channels & (1 << channelIndex)) != 0) {
            channel_dispatcher::clearProtection(Channel::get(channelIndex));
        }
    }

    return SCPI_RES_OK;
}


scpi_result_t scpi_cmd_outputState(scpi_t *context) {
    bool enable;
    if (!SCPI_ParamBool(context, &enable, TRUE)) {
        return SCPI_RES_ERR;
    }

    uint32_t channels = param_channels(context);
    if (channels == 0) {
        return SCPI_RES_ERR;
    }

    int err;
    if (!channel_dispatcher::outputEnable(channels, enable, &err)) {
        SCPI_ErrorPush(context, err);
        return SCPI_RES_ERR;
    }

    return SCPI_RES_OK;
}

scpi_result_t scpi_cmd_outputStateQ(scpi_t *context) {
    uint32_t channels = param_channels(context);
    if (channels == 0) {
        return SCPI_RES_ERR;
    }

    for (int channelIndex = 0; channelIndex < CH_NUM; channelIndex++) {
        if ((channels & (1 << channelIndex)) != 0) {
            SCPI_ResultBool(context, Channel::get(channelIndex).isOutputEnabled());
        }
    }

    return SCPI_RES_OK;
}

static const scpi_choice_def_t outputTackChoices[] = {
    {"OFF", 0},
    {"ON",  1},
    {"ALL", 2},
    SCPI_CHOICE_LIST_END /* termination of option list */
};

scpi_result_t scpi_cmd_outputTrackState(scpi_t *context) {
    if (channel_dispatcher::getCouplingType() != channel_dispatcher::COUPLING_TYPE_NONE) {
        SCPI_ErrorPush(context, SCPI_ERROR_EXECUTE_ERROR_CHANNELS_ARE_COUPLED);
        return SCPI_RES_ERR;
    }

    scpi_parameter_t parameter;
    if (!SCPI_Parameter(context, &parameter, true)) {
        return SCPI_RES_ERR;
    }

    uint32_t channels;

    if (parameter.type == SCPI_TOKEN_DECIMAL_NUMERIC_PROGRAM_DATA || parameter.type == SCPI_TOKEN_PROGRAM_MNEMONIC) {
        int32_t outputTackChoice;
        if (
            (parameter.type == SCPI_TOKEN_DECIMAL_NUMERIC_PROGRAM_DATA && !SCPI_ParamToInt32(context, &parameter, &outputTackChoice)) ||
            !SCPI_ParamToChoice(context, &parameter, outputTackChoices, &outputTackChoice)
        ) {
            SCPI_ErrorPush(context, SCPI_ERROR_ILLEGAL_PARAMETER_VALUE);
            return SCPI_RES_ERR;
        }

        if (outputTackChoice != 0 && outputTackChoice != 2) {
            SCPI_ErrorPush(context, SCPI_ERROR_ILLEGAL_PARAMETER_VALUE);
            return SCPI_RES_ERR;
        }

        if (outputTackChoice == 0) {
            channel_dispatcher::setTrackingChannels(0);
            return SCPI_RES_OK;
        }

        channels = 0xFFFFFFFF; // all channels
    } else {
        channels = param_channels(context, &parameter);
        if (channels == 0) {
            return SCPI_RES_ERR;
        }
    }

    int numChannels = 0;

    for (int channelIndex = 0; channelIndex < CH_NUM; channelIndex++) {
        if ((channels & (1 << channelIndex)) != 0) {
            int err;
            if (!channel_dispatcher::isTrackingAllowed(Channel::get(channelIndex), &err)) {
                SCPI_ErrorPush(context, err);
                return SCPI_RES_ERR;
            }

            numChannels++;
        }
    }

    if (numChannels >= 2) {
        channel_dispatcher::setTrackingChannels(channels);
    } else {
        SCPI_ErrorPush(context, SCPI_ERROR_ILLEGAL_PARAMETER_VALUE);
        return SCPI_RES_ERR;
    }

    return SCPI_RES_OK;
}

scpi_result_t scpi_cmd_outputTrackStateQ(scpi_t *context) {
    uint32_t channels = param_channels(context);
    if (channels == 0) {
        return SCPI_RES_ERR;
    }

    for (int channelIndex = 0; channelIndex < CH_NUM; channelIndex++) {
        if ((channels & (1 << channelIndex)) != 0) {
            SCPI_ResultBool(context, Channel::get(channelIndex).flags.trackingEnabled ? true : false);
        }
    }

    return SCPI_RES_OK;
}

scpi_result_t scpi_cmd_outputProtectionCouple(scpi_t *context) {
    bool enable;
    if (!SCPI_ParamBool(context, &enable, TRUE)) {
        return SCPI_RES_ERR;
    }

    persist_conf::enableOutputProtectionCouple(enable);

    return SCPI_RES_OK;
}

scpi_result_t scpi_cmd_outputProtectionCoupleQ(scpi_t *context) {
    SCPI_ResultBool(context, persist_conf::isOutputProtectionCoupleEnabled());

    return SCPI_RES_OK;
}

scpi_result_t scpi_cmd_outputStateTriggered(scpi_t *context) {
    bool enable;
    if (!SCPI_ParamBool(context, &enable, TRUE)) {
        return SCPI_RES_ERR;
    }

    Channel *channel = param_channel(context);
    if (!channel) {
        return SCPI_RES_ERR;
    }

    channel_dispatcher::setTriggerOutputState(*channel, enable);

    return SCPI_RES_OK;
}

scpi_result_t scpi_cmd_outputStateTriggeredQ(scpi_t *context) {
    Channel *channel = param_channel(context);
    if (!channel) {
        return SCPI_RES_ERR;
    }

    SCPI_ResultBool(context, channel_dispatcher::getTriggerOutputState(*channel));

    return SCPI_RES_OK;
}

scpi_result_t scpi_cmd_outputDprog(scpi_t *context) {
    bool enable;
    if (!SCPI_ParamBool(context, &enable, TRUE)) {
        return SCPI_RES_ERR;
    }

    Channel *channel = param_channel(context);
    if (!channel) {
        return SCPI_RES_ERR;
    }

    if (channel->params.features & CH_FEATURE_DPROG) {
        channel->setDprogState((DprogState)enable);
    } else {
        SCPI_ErrorPush(context, SCPI_ERROR_HARDWARE_MISSING);
        return SCPI_RES_ERR;
    }

    return SCPI_RES_OK;
}

scpi_result_t scpi_cmd_outputDprogQ(scpi_t *context) {
    Channel *channel = param_channel(context);
    if (!channel) {
        return SCPI_RES_ERR;
    }

    if (channel->params.features & CH_FEATURE_DPROG) {
        SCPI_ResultBool(context, channel->flags.dprogState);
    } else {
        SCPI_ErrorPush(context, SCPI_ERROR_HARDWARE_MISSING);
        return SCPI_RES_ERR;
    }

    return SCPI_RES_OK;
}

scpi_result_t scpi_cmd_outputDelayDuration(scpi_t *context) {
    scpi_number_t param;
    if (!SCPI_ParamNumber(context, scpi_special_numbers_def, &param, true)) {
        return SCPI_RES_ERR;
    }
    float duration;
    if (param.special) {
        if (param.content.tag == SCPI_NUM_MIN) {
            duration = OUTPUT_DELAY_DURATION_MIN_VALUE;
        } else if (param.content.tag == SCPI_NUM_MAX) {
            duration = OUTPUT_DELAY_DURATION_MAX_VALUE;
        } else if (param.content.tag == SCPI_NUM_DEF) {
            duration = OUTPUT_DELAY_DURATION_DEF_VALUE;
        } else {
            SCPI_ErrorPush(context, SCPI_ERROR_ILLEGAL_PARAMETER_VALUE);
            return SCPI_RES_ERR;
        }
    } else {
        if (param.unit != SCPI_UNIT_NONE && param.unit != SCPI_UNIT_SECOND) {
            SCPI_ErrorPush(context, SCPI_ERROR_INVALID_SUFFIX);
            return SCPI_RES_ERR;
        }

        duration = (float)param.content.value;
    }

    Channel *channel = param_channel(context);
    if (!channel) {
        return SCPI_RES_ERR;
    }

    channel_dispatcher::setOutputDelayDuration(*channel, duration);

    return SCPI_RES_OK;
}

scpi_result_t scpi_cmd_outputDelayDurationQ(scpi_t *context) {
    Channel *channel = param_channel(context);
    if (!channel) {
        return SCPI_RES_ERR;
    }

    return get_source_value(context, *channel, UNIT_SECOND, channel->outputDelayDuration, OUTPUT_DELAY_DURATION_MIN_VALUE, OUTPUT_DELAY_DURATION_MAX_VALUE, OUTPUT_DELAY_DURATION_DEF_VALUE);
}

} // namespace scpi
} // namespace psu
} // namespace eez
