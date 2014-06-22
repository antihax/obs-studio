/******************************************************************************
    Copyright (C) 2014 by Hugh Bailey <obs.jim@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
******************************************************************************/

#pragma once

#include "util/c99defs.h"
#include "obs-data.h"

#ifdef __cplusplus
extern "C" {
#endif

enum obs_property_type {
	OBS_PROPERTY_INVALID,
	OBS_PROPERTY_BOOL,
	OBS_PROPERTY_INT,
	OBS_PROPERTY_FLOAT,
	OBS_PROPERTY_TEXT,
	OBS_PROPERTY_PATH,
	OBS_PROPERTY_LIST,
	OBS_PROPERTY_COLOR,
	OBS_PROPERTY_BUTTON,
};

enum obs_combo_format {
	OBS_COMBO_FORMAT_INVALID,
	OBS_COMBO_FORMAT_INT,
	OBS_COMBO_FORMAT_FLOAT,
	OBS_COMBO_FORMAT_STRING
};

enum obs_combo_type {
	OBS_COMBO_TYPE_INVALID,
	OBS_COMBO_TYPE_EDITABLE,
	OBS_COMBO_TYPE_LIST,
};

enum obs_text_type {
	OBS_TEXT_DEFAULT,
	OBS_TEXT_PASSWORD,
};

struct obs_properties;
struct obs_property;
typedef struct obs_properties *obs_properties_t;
typedef struct obs_property   *obs_property_t;

/* ------------------------------------------------------------------------- */

EXPORT obs_properties_t obs_properties_create(const char *locale);
EXPORT obs_properties_t obs_properties_create_param(const char *locale,
		void *param, void (*destroy)(void *param));
EXPORT void obs_properties_destroy(obs_properties_t props);

EXPORT void obs_properties_set_param(obs_properties_t props,
		void *param, void (*destroy)(void *param));
EXPORT void *obs_properties_get_param(obs_properties_t props);

EXPORT const char *obs_properties_locale(obs_properties_t props);

EXPORT obs_property_t obs_properties_first(obs_properties_t props);

EXPORT obs_property_t obs_properties_get(obs_properties_t props,
		const char *property);

/* used internally by libobs */
extern void obs_properties_apply_settings(obs_properties_t props,
		obs_data_t settings);

/* ------------------------------------------------------------------------- */

/**
 * Callback for when a button property is clicked.  If the properties
 * need to be refreshed due to changes to the property layout, return true,
 * otherwise return false.
 */
typedef bool (*obs_property_clicked_t)(obs_properties_t props,
		obs_property_t property, void *data);

EXPORT obs_property_t obs_properties_add_bool(obs_properties_t props,
		const char *name, const char *description);

EXPORT obs_property_t obs_properties_add_int(obs_properties_t props,
		const char *name, const char *description,
		int min, int max, int step);

EXPORT obs_property_t obs_properties_add_float(obs_properties_t props,
		const char *name, const char *description,
		double min, double max, double step);

EXPORT obs_property_t obs_properties_add_text(obs_properties_t props,
		const char *name, const char *description,
		enum obs_text_type type);

EXPORT obs_property_t obs_properties_add_path(obs_properties_t props,
		const char *name, const char *description);

EXPORT obs_property_t obs_properties_add_list(obs_properties_t props,
		const char *name, const char *description,
		enum obs_combo_type type, enum obs_combo_format format);

EXPORT obs_property_t obs_properties_add_color(obs_properties_t props,
		const char *name, const char *description);

EXPORT obs_property_t obs_properties_add_button(obs_properties_t props,
		const char *name, const char *text,
		obs_property_clicked_t callback);

/* ------------------------------------------------------------------------- */

/**
 * Optional callback for when a property is modified.  If the properties
 * need to be refreshed due to changes to the property layout, return true,
 * otherwise return false.
 */
typedef bool (*obs_property_modified_t)(obs_properties_t props,
		obs_property_t property, obs_data_t settings);

EXPORT void obs_property_set_modified_callback(obs_property_t p,
		obs_property_modified_t modified);

EXPORT bool obs_property_modified(obs_property_t p, obs_data_t settings);
EXPORT bool obs_property_button_clicked(obs_property_t p, void *obj);

EXPORT void obs_property_set_visible(obs_property_t p, bool visible);
EXPORT void obs_property_set_enabled(obs_property_t p, bool enabled);

EXPORT const char *           obs_property_name(obs_property_t p);
EXPORT const char *           obs_property_description(obs_property_t p);
EXPORT enum obs_property_type obs_property_get_type(obs_property_t p);
EXPORT bool                   obs_property_enabled(obs_property_t p);
EXPORT bool                   obs_property_visible(obs_property_t p);

EXPORT bool                   obs_property_next(obs_property_t *p);

EXPORT int                    obs_property_int_min(obs_property_t p);
EXPORT int                    obs_property_int_max(obs_property_t p);
EXPORT int                    obs_property_int_step(obs_property_t p);
EXPORT double                 obs_property_float_min(obs_property_t p);
EXPORT double                 obs_property_float_max(obs_property_t p);
EXPORT double                 obs_property_float_step(obs_property_t p);
EXPORT enum obs_text_type     obs_proprety_text_type(obs_property_t p);
EXPORT enum obs_combo_type    obs_property_list_type(obs_property_t p);
EXPORT enum obs_combo_format  obs_property_list_format(obs_property_t p);

EXPORT void obs_property_list_clear(obs_property_t p);

EXPORT size_t obs_property_list_add_string(obs_property_t p,
		const char *name, const char *val);
EXPORT size_t obs_property_list_add_int(obs_property_t p,
		const char *name, long long val);
EXPORT size_t obs_property_list_add_float(obs_property_t p,
		const char *name, double val);

EXPORT void obs_property_list_item_disable(obs_property_t p, size_t idx,
								bool disabled);
EXPORT bool obs_property_list_item_disabled(obs_property_t p, size_t idx);

EXPORT void obs_property_list_remove(obs_property_t p, size_t idx);

EXPORT size_t      obs_property_list_item_count(obs_property_t p);
EXPORT const char *obs_property_list_item_name(obs_property_t p, size_t idx);
EXPORT const char *obs_property_list_item_string(obs_property_t p, size_t idx);
EXPORT long long   obs_property_list_item_int(obs_property_t p, size_t idx);
EXPORT double      obs_property_list_item_float(obs_property_t p, size_t idx);

#ifdef __cplusplus
}
#endif
