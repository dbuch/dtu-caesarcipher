/* dtu-caesarcipher-perspective.c
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

#include "dtu-caesarcipher-perspective.h"

typedef struct
{
  GtkWidget *current_active;
  GtkWidget *previous;
} DtuCaesarcipherPerspectivePrivate;

G_DEFINE_TYPE_WITH_PRIVATE (DtuCaesarcipherPerspective, dtu_caesarcipher_perspective, GTK_TYPE_STACK)

enum {
  PROP_0,
  N_PROPS
};

static GParamSpec *properties [N_PROPS];

DtuCaesarcipherPerspective *
dtu_caesarcipher_perspective_new (void)
{
  return g_object_new (DTU_TYPE_CAESARCIPHER_PERSPECTIVE, NULL);
}

static void
dtu_caesarcipher_perspective_finalize (GObject *object)
{
  DtuCaesarcipherPerspective *self = (DtuCaesarcipherPerspective *)object;
  DtuCaesarcipherPerspectivePrivate *priv = dtu_caesarcipher_perspective_get_instance_private (self);

  G_OBJECT_CLASS (dtu_caesarcipher_perspective_parent_class)->finalize (object);
}

static void
dtu_caesarcipher_perspective_get_property (GObject    *object,
                                           guint       prop_id,
                                           GValue     *value,
                                           GParamSpec *pspec)
{
  DtuCaesarcipherPerspective *self = DTU_CAESARCIPHER_PERSPECTIVE (object);

  switch (prop_id)
    {
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

static void
dtu_caesarcipher_perspective_set_property (GObject      *object,
                                           guint         prop_id,
                                           const GValue *value,
                                           GParamSpec   *pspec)
{
  DtuCaesarcipherPerspective *self = DTU_CAESARCIPHER_PERSPECTIVE (object);

  switch (prop_id)
    {
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

static void
dtu_caesarcipher_perspective_switch_default(DtuCaesarcipherPerspective *self,
                                            GtkWidget *page)
{
  DtuCaesarcipherPerspectivePrivate *priv = dtu_caesarcipher_perspective_get_instance_private (self);

  priv->current_active = page;
  priv->previous = priv->current_active;

  gtk_stack_set_visible_child (GTK_STACK (self), page);
}

static void
dtu_caesarcipher_perspective_class_init (DtuCaesarcipherPerspectiveClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);

  object_class->finalize = dtu_caesarcipher_perspective_finalize;
  object_class->get_property = dtu_caesarcipher_perspective_get_property;
  object_class->set_property = dtu_caesarcipher_perspective_set_property;

  klass->switch_to = dtu_caesarcipher_perspective_switch;
}

static void
dtu_caesarcipher_perspective_init (DtuCaesarcipherPerspective *self)
{
}


void
dtu_caesarcipher_perspective_switch(DtuCaesarcipherPerspective *self,
                                    GtkWidget                  *page)
{
  DtuCaesarcipherPerspectiveClass *perspective_class =
        DTU_CAESARCIPHER_PERSPECTIVE_GET_CLASS (self);

  g_print ("test\n");
  perspective_class->switch_to(self, page);
}
