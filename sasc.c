/*
 *      This program is free software: you can redistribute it and/or modify
 *      it under the terms of the GNU General Public License as published by
 *      the Free Software Foundation, either version 3 of the License, or
 *      (at your option) any later version.
 * 
 *      This program is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *      GNU General Public License for more details.
 *      You should have received a copy of the GNU General Public License
 *      along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "sasc-structure.h"
#include "callback.h"
#include "widget.h"

#include <gtk/gtk.h>

extern int set_sa(uint controller, uint device);

int main(int argc, char *argv[]) {
	sasc_data wg_data;

	gtk_init(&argc, &argv);
	
	if (set_sa(GPIB_INTERFACE,GPIB_ADR))	{
		wdg_main(&wg_data);
		wdg_menu(&wg_data);
		wdg_sasettings(&wg_data);

		gtk_widget_show_all(wg_data.main_window);
		time_handler(&wg_data); 
		 
		gtk_main();

		return 0;  	
	}
	return -1;
}

