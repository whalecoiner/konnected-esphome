/*
 * Copyright (C) 2024  Konnected Inc.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "esphome/components/cover/cover.h"
#include "esphome/core/component.h"
#include "automation.h"
#include "../gdolib.h"

namespace esphome {
namespace secplus_gdo {

using namespace esphome::cover;
    class GDODoor : public cover::Cover, public Component {
    public:
        cover::CoverTraits get_traits() override {
            auto traits = CoverTraits();
            traits.set_supports_stop(true);
            traits.set_supports_toggle(true);
            traits.set_supports_position(true);
            return traits;
        }

        void register_door_closing_warn_start_trigger(CoverClosingStartTrigger *trigger) {
            this->pre_close_start_trigger = trigger;
        }

        void register_door_closing_warn_end_trigger(CoverClosingEndTrigger *trigger) {
            this->pre_close_end_trigger = trigger;
        }

        void start_pre_close(uint32_t pos = 0);
        void set_pre_close_warning_duration(uint32_t ms) { this->pre_close_duration_ = ms; }
        void set_state(gdo_door_state_t state, float position);

    protected:
        void control(const cover::CoverCall& call);

        CoverClosingStartTrigger *pre_close_start_trigger{nullptr};
        CoverClosingEndTrigger   *pre_close_end_trigger{nullptr};
        uint32_t                 pre_close_duration_{0};
        bool                     pre_close_active_{false};
    };
} // namespace secplus_gdo
} // namespace esphome
