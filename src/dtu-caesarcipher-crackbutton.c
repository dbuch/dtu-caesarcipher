/* dtu-caesarcipher-crackbutton.c
 *
 * Copyright (C) 2017 Daniel Buch <boogiewasthere@gmail.com>
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

#include "dtu-caesarcipher-crackbutton.h"

typedef struct
{
  gint current_state;

} DtuCaesarcipherCrackbuttonPrivate;

G_DEFINE_TYPE_WITH_PRIVATE (DtuCaesarcipherCrackbutton, dtu_caesarcipher_crackbutton, GTK_TYPE_BUTTON)

enum {
  PROP_0,
  PROP_STATE,
  N_PROPS
};

enum {
  STATE_CRACK,
  STATE_BACK,
};

static GParamSpec *properties [N_PROPS];

DtuCaesarcipherCrackbutton *
dtu_caesarcipher_crackbutton_new (void)
{
  return g_object_new (DTU_TYPE_CAESARCIPHER_CRACKBUTTON, NULL);
}

static void
dtu_caesarcipher_crackbutton_finalize (GObject *object)
{
  DtuCaesarcipherCrackbutton *self = (DtuCaesarcipherCrackbutton *)object;

  G_OBJECT_CLASS (dtu_caesarcipher_crackbutton_parent_class)->finalize (object);
}

static void
dtu_caesarcipher_crackbutton_get_property (GObject    *object,
                                           guint       prop_id,
                                           GValue     *value,
                                           GParamSpec *pspec)
{
  DtuCaesarcipherCrackbutton *self = DTU_CAESARCIPHER_CRACKBUTTON (object);
  DtuCaesarcipherCrackbuttonPrivate *priv = dtu_caesarcipher_crackbutton_get_instance_private (self);

  switch (prop_id)
    {
    case PROP_STATE:
      g_value_set_int (value, priv->current_state);
    break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

static void
dtu_caesarcipher_crackbutton_set_property (GObject      *object,
                                           guint         prop_id,
                                           const GValue *value,
                                           GParamSpec   *pspec)
{
  DtuCaesarcipherCrackbutton *self = DTU_CAESARCIPHER_CRACKBUTTON (object);
  DtuCaesarcipherCrackbuttonPrivate *priv = dtu_caesarcipher_crackbutton_get_instance_private (self);


  switch (prop_id)
    {
    case PROP_STATE:
      priv->current_state = g_value_get_int (value);
    break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

static void
dtu_caesarcipher_crackbutton_class_init (DtuCaesarcipherCrackbuttonClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);
  GtkButtonClass *button_class = GTK_BUTTON_CLASS (klass);

  object_class->finalize = dtu_caesarcipher_crackbutton_finalize;
  object_class->get_property = dtu_caesarcipher_crackbutton_get_property;
  object_class->set_property = dtu_caesarcipher_crackbutton_set_property;

  properties [PROP_STATE] =
    g_param_spec_int ("state", "State", "CrackButtonState",
                      STATE_CRACK, STATE_BACK, STATE_CRACK,
                      G_PARAM_READWRITE);

  g_object_class_install_properties (object_class, N_PROPS, properties);
}

static void
dtu_caesarcipher_crackbutton_init (DtuCaesarcipherCrackbutton *self)
{
}
