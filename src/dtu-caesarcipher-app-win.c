/* dtu-caesarcipher-app-win.c
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

#include "dtu-caesarcipher-app-win.h"
#include "dtu-caesarcipher.h"
#include "dtu-caesarcipher-language.h"
#include "dtu-caesarcipher-crackbutton.h"
#include <gspell/gspell.h>

typedef struct
{
  gpointer dummy;
} DtuCaesarcipherAppWinPrivate;

G_DEFINE_TYPE_WITH_PRIVATE (DtuCaesarcipherAppWin, dtu_caesarcipher_app_win, GTK_TYPE_APPLICATION_WINDOW)

DtuCaesarcipherAppWin *
dtu_caesarcipher_app_win_new (GtkApplication *app)
{
  return g_object_new (DTU_TYPE_CAESARCIPHER_APP_WIN,
                       "application", app,
                        NULL);
}

static void
dtu_caesarcipher_app_win_finalize (GObject *object)
{
  DtuCaesarcipherAppWin *self = (DtuCaesarcipherAppWin *)object;

  G_OBJECT_CLASS (dtu_caesarcipher_app_win_parent_class)->finalize (object);
}

static void
dtu_caesarcipher_app_win_class_init (DtuCaesarcipherAppWinClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS(klass);
  GAction *action = NULL;

  object_class->finalize = dtu_caesarcipher_app_win_finalize;

  gtk_widget_class_set_template_from_resource (widget_class, "/org/gnome/DtuCaesarcipher/dtu-caesarcipher-application.ui");
  gtk_widget_class_bind_template_child (widget_class, DtuCaesarcipherAppWin, crack_btn);
  gtk_widget_class_bind_template_child (widget_class, DtuCaesarcipherAppWin, stack_view);
  gtk_widget_class_bind_template_child (widget_class, DtuCaesarcipherAppWin, result_view);
  gtk_widget_class_bind_template_child (widget_class, DtuCaesarcipherAppWin, encrypted_view);
  gtk_widget_class_bind_template_child (widget_class, DtuCaesarcipherAppWin, spinner);
  gtk_widget_class_bind_template_child (widget_class, DtuCaesarcipherAppWin, key_lbl);
  gtk_widget_class_bind_template_child (widget_class, DtuCaesarcipherAppWin, preferences_btn);
  gtk_widget_class_bind_template_child (widget_class, DtuCaesarcipherAppWin, preferences_view);
}

static void
dtu_caesarcipher_app_win_init (DtuCaesarcipherAppWin *self)
{
  g_type_ensure (DTU_TYPE_CAESARCIPHER_CRACKBUTTON);
  gtk_widget_init_template (GTK_WIDGET(self));

  self->languages = gspell_language_chooser_button_new (NULL);

  gtk_widget_show (self->languages);
  gtk_container_add(GTK_CONTAINER(self->preferences_view), GTK_WIDGET(self->languages));
}
