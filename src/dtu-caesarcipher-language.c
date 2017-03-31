/* dtu-caesarcipher-language.c
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

#include "dtu-caesarcipher-language.h"

typedef struct
{
  const GspellLanguage *language;
  guint default_language : 1;
} DtuCaesarcipherLanguagePrivate;

struct _DtuCaesarcipherLanguage
{
  GtkComboBox parent_instance;
};

enum
{
  COLUMN_LANGUAGE_NAME,
  COLUMN_LANGUAGE_POINTER,
  N_COLUMNS,
};

enum
{
  PROP_0,
  PROP_LANGUAGE,
  PROP_LANGUAGE_CODE,
  N_PROPS,
};

static void dtu_caesarcipher_language_interface_init(GspellLanguageChooserInterface *iface);

G_DEFINE_TYPE_WITH_CODE (DtuCaesarcipherLanguage,
                         dtu_caesarcipher_language,
                         GTK_TYPE_COMBO_BOX,
                         G_IMPLEMENT_INTERFACE (GSPELL_TYPE_LANGUAGE_CHOOSER,
                                                dtu_caesarcipher_language_interface_init))

static GParamSpec *properties [N_PROPS];

DtuCaesarcipherLanguage *
dtu_caesarcipher_language_new (void)
{
  return g_object_new (DTU_TYPE_CAESARCIPHER_LANGUAGE,
                       "visible", TRUE,
                       "language", NULL,
                       NULL);
}

static void
dtu_caesarcipher_language_finalize (GObject *object)
{
  DtuCaesarcipherLanguage *self = (DtuCaesarcipherLanguage *)object;

  G_OBJECT_CLASS (dtu_caesarcipher_language_parent_class)->finalize (object);
}

static void
dtu_caesarcipher_language_get_property (GObject    *object,
                                        guint       prop_id,
                                        GValue     *value,
                                        GParamSpec *pspec)
{
  DtuCaesarcipherLanguage *self = DTU_CAESARCIPHER_LANGUAGE (object);
  GspellLanguageChooser *chooser = GSPELL_LANGUAGE_CHOOSER (object);


  switch (prop_id)
    {
    case PROP_LANGUAGE:
      g_value_set_boxed (value, gspell_language_chooser_get_language (chooser));
    break;
    case PROP_LANGUAGE_CODE:
      g_value_set_string (value, gspell_language_chooser_get_language_code (chooser));
    break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

static void
dtu_caesarcipher_language_set_property (GObject      *object,
                                        guint         prop_id,
                                        const GValue *value,
                                        GParamSpec   *pspec)
{
  GspellLanguageChooser *chooser = GSPELL_LANGUAGE_CHOOSER (object);

  switch (prop_id)
    {
    case PROP_LANGUAGE:
      gspell_language_chooser_set_language (chooser, g_value_get_boxed (value));
    break;
    case PROP_LANGUAGE_CODE:
      gspell_language_chooser_set_language_code (chooser, g_value_get_string (value));
    break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

static void
dtu_caesarcipher_language_class_init (DtuCaesarcipherLanguageClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);

  object_class->finalize = dtu_caesarcipher_language_finalize;
  object_class->get_property = dtu_caesarcipher_language_get_property;
  object_class->set_property = dtu_caesarcipher_language_set_property;

  g_object_class_override_property (object_class, PROP_LANGUAGE, "language");
  g_object_class_override_property (object_class, PROP_LANGUAGE_CODE, "language-code");
}

static void
changed_cb(DtuCaesarcipherLanguage *self,
           gpointer                 user_data)
{
  DtuCaesarcipherLanguagePrivate *priv = dtu_caesarcipher_language_get_instance_private (self);
  GtkListStore *store = GTK_LIST_STORE (gtk_combo_box_get_model (GTK_COMBO_BOX (self)));
  GtkTreeIter iter;
  const GspellLanguage *language;

  gtk_combo_box_get_active_iter (GTK_COMBO_BOX (self), &iter);
  gtk_tree_model_get (GTK_TREE_MODEL (store), &iter, COLUMN_LANGUAGE_POINTER, &language, -1);
  gspell_language_chooser_set_language (GSPELL_LANGUAGE_CHOOSER (self), language);
}

static void
dtu_caesarcipher_language_init (DtuCaesarcipherLanguage *self)
{
  GtkCellRenderer *renderer;
  g_autoptr(GtkListStore) store;
  const GList *available_languages, *l;

  store = gtk_list_store_new (N_COLUMNS, G_TYPE_STRING, GSPELL_TYPE_LANGUAGE);
  gtk_combo_box_set_model (GTK_COMBO_BOX(self), GTK_TREE_MODEL (store));

  renderer = gtk_cell_renderer_text_new ();
  gtk_cell_layout_pack_start (GTK_CELL_LAYOUT (self), renderer, TRUE);
  gtk_cell_layout_set_attributes (GTK_CELL_LAYOUT (self), renderer,
                                  "text", COLUMN_LANGUAGE_NAME,
                                  NULL);


  available_languages = gspell_language_get_available ();

  for(l = available_languages; l; l = l->next)
    {
      const GspellLanguage *lang = l->data;
      GtkTreeIter iter;
      const gchar *name;

      name = gspell_language_get_name (lang);

      gtk_list_store_append (store, &iter);
      gtk_list_store_set(store, &iter,
                         COLUMN_LANGUAGE_NAME, name,
                         COLUMN_LANGUAGE_POINTER, lang,
                         -1);

    }

  gtk_combo_box_set_id_column (GTK_COMBO_BOX (self), COLUMN_LANGUAGE_NAME);

  g_signal_connect (self, "changed", G_CALLBACK(changed_cb), NULL);
}

static void
dtu_caesarcipher_language_set_language(GspellLanguageChooser *chooser,
                                       const GspellLanguage  *language_param)
{
  DtuCaesarcipherLanguage *self = DTU_CAESARCIPHER_LANGUAGE (chooser);
  DtuCaesarcipherLanguagePrivate *priv = dtu_caesarcipher_language_get_instance_private (self);
  GtkTreeModel*store;
  GtkTreeIter iter;
  const GspellLanguage *language;

 	language = language_param;

	if (language == NULL)
	{
		language = gspell_language_get_default ();
	}

	if (language == NULL)
	{
		gboolean notify_language_code = FALSE;

		if (!priv->default_language)
		{
			priv->default_language = TRUE;
			notify_language_code = TRUE;
		}

		if (priv->language != NULL)
		{
			priv->language = NULL;
			g_object_notify (G_OBJECT (self), "language");
		}

		if (notify_language_code)
		{
			g_object_notify (G_OBJECT (self), "language-code");
		}

		return;
	}

  store = gtk_combo_box_get_model (GTK_COMBO_BOX(self));

  if(!gtk_tree_model_get_iter_first (GTK_TREE_MODEL (store), &iter))
    return;

  do
  {
    const GspellLanguage *current_language;
    gtk_tree_model_get (GTK_TREE_MODEL (store), &iter,
                        COLUMN_LANGUAGE_POINTER, &current_language,
                        -1);

    if(language == current_language)
      {
        gboolean default_language = language_param == NULL;
        gboolean notify_language_code = FALSE;

        if (priv->default_language != default_language)
          {
            priv->default_language = default_language;
            notify_language_code = TRUE;
          }

        if(priv->language != language)
          {
            priv->language = language;
            g_object_notify (G_OBJECT (self), "language");
            notify_language_code = TRUE;
          }

        if(notify_language_code)
          {
            g_object_notify (G_OBJECT (self), "language-code");
          }

        return;
      }
  }
  while(gtk_tree_model_iter_next (GTK_TREE_MODEL (store), &iter));
}

static const GspellLanguage*
dtu_caesarcipher_language_get_language_full(GspellLanguageChooser *chooser,
                                            gboolean              *default_language)
{
  DtuCaesarcipherLanguage *language = DTU_CAESARCIPHER_LANGUAGE (chooser);
  DtuCaesarcipherLanguagePrivate *priv = dtu_caesarcipher_language_get_instance_private (language);

  if(default_language)
    *default_language = priv->default_language;

  return priv->language;
}


static void dtu_caesarcipher_language_interface_init(GspellLanguageChooserInterface *iface)
{
  iface->get_language_full = dtu_caesarcipher_language_get_language_full;
  iface->set_language = dtu_caesarcipher_language_set_language;
}
