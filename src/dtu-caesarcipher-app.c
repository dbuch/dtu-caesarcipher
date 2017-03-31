
/* dtu-caesarcipher-app.c
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
#include "dtu-caesarcipher-app.h"
#include "dtu-caesarcipher.h"

typedef struct
{
  DtuCaesarcipherAppWin *win;
  DtuCaesarcipher *caesar_cipher;
} widget_container;

struct _DtuCaesarcipherApp
{
  GtkApplication parent_instance;
};

G_DEFINE_TYPE(DtuCaesarcipherApp, dtu_caesarcipher_app, GTK_TYPE_APPLICATION)

DtuCaesarcipherApp *
dtu_caesarcipher_app_new (void)
{
  return g_object_new (DTU_TYPE_CAESARCIPHER_APP,
                       "application-id", "org.gnome.DtuCaesarcipher",
                       "flags", G_APPLICATION_FLAGS_NONE,
                       NULL);
}

static void
dtu_caesarcipher_app_finalize (GObject *object)
{
  DtuCaesarcipherApp *self = (DtuCaesarcipherApp *)object;

  G_OBJECT_CLASS (dtu_caesarcipher_app_parent_class)->finalize (object);
}

static void
crack_finished_cb(GObject *object,
                  GAsyncResult *result,
                  gpointer user_data)
{
  DtuCaesarcipher *self = DTU_CAESARCIPHER (object);
  widget_container *widgets = user_data;
  GError *error = NULL;
  gchar *res;

  res = dtu_caesarcipher_crack_finish (result, &error);
  if(res)
    {
      GtkTextView *result_view = GTK_TEXT_VIEW(gtk_stack_get_child_by_name (widgets->win->stack_view, "result_view"));
      GtkTextBuffer *buf = gtk_text_view_get_buffer (result_view);

      gtk_text_buffer_insert_at_cursor (buf, res, -1);
      gtk_stack_set_visible_child_name (widgets->win->stack_view, "result_view");
    }
  else
    {
      gtk_label_set_text (widgets->win->key_lbl, error->message);
    }
  gtk_spinner_stop(widgets->win->spinner);
  gtk_button_set_label (widgets->win->crack_btn, "Back");
}

static void
crack_btn_clicked_cb(GtkButton *btn,
                     gpointer  *user_data)
{
  widget_container *container = (widget_container*)user_data;

  const gchar *lbl = gtk_button_get_label(container->win->crack_btn);

  if (g_str_equal (lbl, "Crack it!"))
    dtu_caesarcipher_crack_async (container->caesar_cipher, NULL, crack_finished_cb, container);
  else
    {
      gtk_stack_set_visible_child_name (container->win->stack_view, "encrypted_view");
      gtk_label_set_text (container->win->key_lbl, "");
      gtk_button_set_label (container->win->crack_btn, "Crack it!");

      GtkTextIter start, end;

      GtkTextBuffer *buf = gtk_text_view_get_buffer(container->win->result_view);
      gtk_text_buffer_get_end_iter (buf, &end);
      gtk_text_buffer_get_start_iter (buf, &start);

      gtk_text_buffer_delete (buf, &start, &end);
    }
}

static void
key_changed_cb(GObject *obj,
               GParamSpec *pspec,
               gpointer user_data)
{
  DtuCaesarcipher *self = DTU_CAESARCIPHER(obj);
  GtkLabel *lbl = GTK_LABEL(user_data);

  g_autofree gchar *string = g_strdup_printf ("Key: %d", self->key);

  gtk_label_set_text (lbl, string);
}

static void
widgets_free(gpointer data, GClosure *closure)
{
  g_free(data);
}


static void
properties_view_cb(GtkToggleButton *btn,
                   gpointer   user_data)
{
  DtuCaesarcipherAppWin *win = DTU_CAESARCIPHER_APP_WIN(user_data);

  guint previous_duration = gtk_stack_get_transition_duration (win->stack_view);

  gtk_stack_set_transition_duration (win->stack_view, 200);

  if(gtk_toggle_button_get_active (btn))
    gtk_stack_set_visible_child_name (win->stack_view, "preferences_view");
  else
    gtk_stack_set_visible_child_name (win->stack_view, "encrypted_view");

  gtk_stack_set_transition_duration (win->stack_view, previous_duration);

}

static void
dtu_caesarcipher_app_activate(GApplication *app)
{
  DtuCaesarcipherAppWin *win = dtu_caesarcipher_app_win_new (GTK_APPLICATION(app));
  DtuCaesarcipher *caesar_cipher = dtu_caesarcipher_new();


  g_signal_connect(G_OBJECT(win->preferences_btn), "toggled", G_CALLBACK(properties_view_cb), win);

  g_object_set(G_OBJECT(caesar_cipher),
               "text", "Ebiil qefp fp x jbppxdb colj JB, AQR fp grpq xebxa - IBQP DL YOL!",
               "key", 0,
               "mode", Encrypt,
               NULL);

  GtkTextBuffer *encrypted_buffer = gtk_text_view_get_buffer (win->encrypted_view);

  g_object_bind_property (G_OBJECT(caesar_cipher), "text",
                          G_OBJECT(encrypted_buffer), "text",
                          G_BINDING_BIDIRECTIONAL | G_BINDING_SYNC_CREATE);

  g_object_bind_property (G_OBJECT(win->languages), "language",
                          G_OBJECT(caesar_cipher), "language",
                          G_BINDING_BIDIRECTIONAL | G_BINDING_SYNC_CREATE);

  widget_container *widgets = g_new0 (widget_container, 1);
  widgets->win = win;
  widgets->caesar_cipher = caesar_cipher;

  g_signal_connect (G_OBJECT(caesar_cipher), "notify::key", G_CALLBACK(key_changed_cb), win->key_lbl);
  g_signal_connect_data (win->crack_btn,
                        "clicked",
                        G_CALLBACK(crack_btn_clicked_cb),
                        widgets, widgets_free, 0);

  gtk_window_present (GTK_WINDOW(win));
}


static void
dtu_caesarcipher_app_class_init (DtuCaesarcipherAppClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  GApplicationClass *app_class = G_APPLICATION_CLASS (klass);

  object_class->finalize = dtu_caesarcipher_app_finalize;
  app_class->activate = dtu_caesarcipher_app_activate;
}

static void
dtu_caesarcipher_app_init (DtuCaesarcipherApp *self)
{

}
