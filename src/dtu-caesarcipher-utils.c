/* dtu-caesarcipher-utils.c
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

#include <gtk/gtk.h>

static GtkWidget **__widget_collection_new_ap(GtkWidget *widget,
                                             va_list    ap)
{
  va_list aq;
  GtkWidget *iter, **res;
  gint n = 0;

  va_copy (aq, ap);

  while((iter = va_arg(aq, GtkWidget*)))
      n++;

  va_end(aq);

  res = g_malloc((n+1) * sizeof(GtkWidget*));

  n = 0;
  iter = NULL;
  while((iter = va_arg(ap, GtkWidget*)))
    {
      res[n++] = iter;
    }

  return res;
}

GtkWidget **widget_collection_new(GtkWidget *widget,
                                 ...)
{
  GtkWidget **ret = NULL;
  va_list ap;

  va_start (ap, widget);

  ret = __widget_collection_new_ap (widget, ap);

  va_end (ap);
}
