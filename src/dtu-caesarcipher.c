/* dtu_caesarcipher.c
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

#include <gio/gio.h>
#include <gspell/gspell.h>
#include "dtu-caesarcipher.h"

typedef struct
{
  GspellChecker *spell_checker;
  GspellLanguage *language;
} DtuCaesarcipherPrivate;

G_DEFINE_TYPE_WITH_PRIVATE (DtuCaesarcipher, dtu_caesarcipher, G_TYPE_OBJECT)

enum {
  PROP_0,
  PROP_TEXT,
  PROP_MODE,
  PROP_KEY,
  PROP_LANGUAGE,
  N_PROPS
};

static GParamSpec *properties [N_PROPS];

DtuCaesarcipher *
dtu_caesarcipher_new ()
{
  return g_object_new (DTU_TYPE_CAESARCIPHER,
                       NULL);
}

static void
dtu_caesarcipher_finalize (GObject *object)
{
  DtuCaesarcipher *self = (DtuCaesarcipher *)object;
  DtuCaesarcipherPrivate *priv = dtu_caesarcipher_get_instance_private (self);

  g_object_unref (priv->spell_checker);

  G_OBJECT_CLASS (dtu_caesarcipher_parent_class)->finalize (object);
}

static void
dtu_caesarcipher_get_property (GObject    *object,
                               guint       prop_id,
                               GValue     *value,
                               GParamSpec *pspec)
{
  DtuCaesarcipher *self = DTU_CAESARCIPHER (object);
  DtuCaesarcipherPrivate *priv = dtu_caesarcipher_get_instance_private (self);

  switch (prop_id)
    {
    case PROP_TEXT:
      g_value_set_string (value, self->text);
    break;

    case PROP_MODE:
      g_value_set_int (value, self->mode);
    break;

    case PROP_KEY:
      g_value_set_int (value, self->key);
    break;

    case PROP_LANGUAGE:
      g_value_set_boxed (value, priv->language);
    break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

static void
dtu_caesarcipher_set_property (GObject      *object,
                               guint         prop_id,
                               const GValue *value,
                               GParamSpec   *pspec)
{
  DtuCaesarcipher *self = DTU_CAESARCIPHER (object);
  DtuCaesarcipherPrivate *priv = dtu_caesarcipher_get_instance_private (self);

  switch (prop_id)
    {
    case PROP_TEXT:
      if(self->text)
        g_free(self->text);
      self->text = g_value_dup_string (value);
    break;
    case PROP_MODE:
      self->mode = g_value_get_int (value);
    break;

    case PROP_KEY:
      self->key = g_value_get_int (value);
    break;
    case PROP_LANGUAGE:
      priv->language = g_value_get_boxed (value);
    break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

static void
dtu_caesarcipher_class_init (DtuCaesarcipherClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);

  object_class->finalize = dtu_caesarcipher_finalize;
  object_class->get_property = dtu_caesarcipher_get_property;
  object_class->set_property = dtu_caesarcipher_set_property;

  properties [PROP_TEXT] =
    g_param_spec_string ("text", "Text", "Text to translate", NULL, G_PARAM_READWRITE);

  properties [PROP_MODE] =
    g_param_spec_int ("mode", "Mode", "Decryption/Encryption Mode", Decrypt, Encrypt, Encrypt, G_PARAM_READWRITE);

  properties [PROP_KEY] =
    g_param_spec_int ("key", "Key", "Decryption/Encryption Key", 0, G_MAXINT, 0, G_PARAM_READWRITE);

  properties [PROP_LANGUAGE] =
    g_param_spec_boxed ("language", "Language", "Language", GSPELL_TYPE_LANGUAGE, G_PARAM_READWRITE);

  g_object_class_install_properties (object_class, N_PROPS, properties);
}

static void
dtu_caesarcipher_init (DtuCaesarcipher *self)
{
  DtuCaesarcipherPrivate *priv = dtu_caesarcipher_get_instance_private (self);

  priv->spell_checker = gspell_checker_new (NULL);
}

static gint
get_case_char(char c)
{
  return g_ascii_isupper (c) ? 'A' : g_ascii_islower (c) ? 'a' : 0;
}

gchar *
dtu_caesarcipher_crypt(DtuCaesarcipher *self, gint key)
{
  gchar *result = g_strdup(self->text);

  if(self->mode == Decrypt)
    key *= -1;

  for(gchar *c = result; *c != '\0'; c++)
    {
      if(g_ascii_isalpha (*c))
        {
          gint casechar = get_case_char(*c);
          gint encrypted = *c - casechar + key;

          if(encrypted < 0)
            encrypted += 26;

          *c = (encrypted % 26) + casechar;
        }
    }
  return result;
}

static gint
g_strlen(gchar *str)
{
  gint res = 0;
  for(gchar *s = str; *s != '\0'; s++)
    res++;

  return res;
}

static gchar *
dtu_caesarcipher_crack(DtuCaesarcipher *self)
{
  DtuCaesarcipherPrivate *priv = dtu_caesarcipher_get_instance_private (self);

  g_object_set (G_OBJECT (priv->spell_checker),
                "language", priv->language,
                NULL);

  self->mode = Encrypt;

  gint key;

  for(gint i = 0; i < 26; i++)
    {
      g_autofree gchar *result = dtu_caesarcipher_crypt (self, i);
      g_auto(GStrv) strv = g_strsplit (result, " ", 0);

      gsize strv_len = g_strv_length (strv);

      gint matches = 0;
      gint required_matches = strv_len / 2 ?: 1;

      for(gchar **s = strv; *s; s++)
        {
          gchar *word = *s;
          GError *error = NULL;
          gint word_len = g_strlen(word);


          if(gspell_checker_check_word(priv->spell_checker, word, word_len, &error))
            matches++;

          if(error)
            {
              g_printerr ("ERROR: %s\n", error->message);
              g_error_free (error);
              return NULL;
            }

          if(matches >= required_matches)
            {

              g_object_set (G_OBJECT(self),
                            "key", i,
                            NULL);

              gchar *ret = result;
              result = NULL;
              return ret;
            }
        }
    }
  return NULL;
}

static void
dtu_caesarcipher_crack_thread_cb(GTask *task,
                                 gpointer source_object,
                                 gpointer task_data,
                                 GCancellable *cancellable)
{
  int retval = 10;
  DtuCaesarcipher *self;
  gchar *result;

  self = g_task_get_source_object (task);

  result = dtu_caesarcipher_crack(self);
  if(result)
      g_task_return_pointer (task, result, NULL);
  else
      g_task_return_new_error (task, g_quark_from_static_string ("NoKey"), 22, "Key: N/A");
}

void
dtu_caesarcipher_crack_async(DtuCaesarcipher    *self,
                             GCancellable       *cancellable,
                             GAsyncReadyCallback callback,
                             gpointer            user_data)
{
  GTask *task = NULL;

  task = g_task_new (self,
                     cancellable,
                     callback,
                     user_data);

  g_task_set_source_tag (task, dtu_caesarcipher_crack_async);

  g_task_set_return_on_cancel (task, FALSE);

  g_task_run_in_thread (task, dtu_caesarcipher_crack_thread_cb);

  g_object_unref (task);
}

gpointer
dtu_caesarcipher_crack_finish(GAsyncResult  *result,
                              GError       **error)
{
  g_return_val_if_fail (G_IS_TASK (result), NULL);

  return g_task_propagate_pointer (G_TASK(result), error);
}

