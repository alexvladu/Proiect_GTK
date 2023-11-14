#include <gtk/gtk.h>
#include<stdio.h>
#include <string.h>
GtkWidget *date, *description, *amount, *income, *expense;
GtkWidget *page_info;
int page=1;
struct transaction{
	int id;
	char *date;
	char *description;
	int amount;
	int type;
};
int check_number(char x)
{
	return x>='0' && x<='9';
}
int transform_chars_to_integer(const char *amount_text)
{
	if(!strlen(amount_text))
		return -1;
	for(int i=0; i<strlen(amount_text); i++)
		if(!check_number(amount_text[i]))
			return -1;
	long long nr=0;
	for(int i=0; i<strlen(amount_text); i++)
		nr*=10, nr+=amount_text[i]-'0';
	return nr;
}
struct transaction create_transaction(char *text)
{
	struct transaction transaction1;
	int ind=0;
	char *aux_id=malloc(20);
	int transaction_id_len=0;
	for(ind; text[ind]!='|'; ind++)
		aux_id[transaction_id_len++]=text[ind];
	aux_id[transaction_id_len]='\0';
	ind++;
	transaction1.id=transform_chars_to_integer(aux_id);
	
	transaction1.date=malloc(15);
	int transaction_date_len=0;
	for(ind; text[ind]!='|'; ind++)
		transaction1.date[transaction_date_len++]=text[ind];
	transaction1.date[transaction_date_len]='\0';
	ind++;
	
	transaction1.description=malloc(100);
	int transaction_desc_len=0;
	for(ind; text[ind]!='|'; ind++)
		transaction1.description[transaction_desc_len++]=text[ind];
	transaction1.description[transaction_desc_len]='\0';
	ind++;
	
	char *aux_amount=malloc(20);
	int transaction_amount_len=0;
	for(ind; text[ind]!='|'; ind++)
		aux_amount[transaction_amount_len++]=text[ind];
	aux_amount[transaction_amount_len]='\0';
	ind++;
	transaction1.amount=transform_chars_to_integer(aux_amount);
	transaction1.type=text[ind]-'0';
	return transaction1;
}
void init_window(GtkWidget *window)
{
	gtk_window_set_title(GTK_WINDOW(window), "Transaction Aplication");
  	gtk_window_set_default_size (GTK_WINDOW (window), 1280, 720);
 	gtk_window_set_resizable(GTK_WINDOW (window), 0);
}
void init_grid(GtkWidget *grid, GtkWidget *add_transaction_button, GtkWidget *show_balance, GtkWidget *display_previous_transactions, GtkWidget *financial_report)
{
	GtkWidget *endline0 = gtk_label_new("");
    GtkWidget *endline1 = gtk_label_new("");
    GtkWidget *endline2 = gtk_label_new("");
    GtkWidget *endline3 = gtk_label_new("");
	gtk_widget_set_size_request(add_transaction_button, 200, 100);
	gtk_widget_set_size_request(show_balance, 200, 100);
	gtk_widget_set_size_request(display_previous_transactions, 200, 100);
	gtk_widget_set_size_request(financial_report, 200, 100);
	
	gtk_grid_attach(GTK_GRID(grid), endline0, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), add_transaction_button, 0, 1, 1, 1);
    
    gtk_grid_attach(GTK_GRID(grid), endline1, 0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), show_balance, 0, 3, 1, 1);
    
    gtk_grid_attach(GTK_GRID(grid), endline2, 0, 4, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), display_previous_transactions, 0, 5, 1, 1);
    
    gtk_grid_attach(GTK_GRID(grid), endline3, 0, 6, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), financial_report, 0, 7, 1, 1);
    
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
}
void init_transaction_modal_entry(GtkWidget *vbox, GtkWidget *date, GtkWidget *description, GtkWidget *amount, GtkWidget *income, GtkWidget *expense, GtkWidget *button_submit)
{
	GtkWidget *grid1 = gtk_grid_new();
   	gtk_widget_set_size_request(date, 200, 50);
	gtk_entry_set_placeholder_text(GTK_ENTRY(date), "Date: (dd.mm.yyyy)");//place holder
	GtkWidget *endline0 = gtk_label_new("");
	gtk_grid_attach(GTK_GRID(grid1), endline0, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid1), date, 1, 1, 1, 1);
    
    gtk_entry_set_placeholder_text(GTK_ENTRY(description), "Description");//place holder
    gtk_grid_attach(GTK_GRID(grid1), description, 1, 3, 1, 1);
    
    gtk_entry_set_placeholder_text(GTK_ENTRY(amount), "Amount of money");//place holder
    gtk_grid_attach(GTK_GRID(grid1), amount, 1, 2, 1, 1);
    	
    GtkWidget *grid2 = gtk_grid_new();
    gtk_grid_attach(GTK_GRID(grid2), income, 1, 3, 1, 1);
	gtk_grid_attach(GTK_GRID(grid2), expense, 2, 3, 1, 1);
	
	GtkWidget *grid3 = gtk_grid_new();
	gtk_widget_set_size_request(button_submit, 100, 50);
	gtk_grid_attach(GTK_GRID(grid3), button_submit, 1, 4, 1, 1);
	
	gtk_widget_set_halign(grid1, GTK_ALIGN_CENTER);
	gtk_widget_set_halign(grid2, GTK_ALIGN_CENTER);
	gtk_widget_set_halign(grid3, GTK_ALIGN_CENTER);
	gtk_box_pack_start(GTK_BOX(vbox), grid1, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), grid2, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), grid3, TRUE, TRUE, 0);
}
int validation_date(GtkWidget *date)
{
	const char *date_text=gtk_entry_get_text(GTK_ENTRY(date));
	if(strlen(date_text)>10)
		return 0;
	for(int i=0; i<=1; i++)
		if(!check_number(date_text[i]))
			return 0;
	if(date_text[2]!='.')
		return 0;
	for(int i=3; i<=4; i++)
		if(!check_number(date_text[i]))
			return 0;
	if(date_text[5]!='.')
		return 0;
	for(int i=6; i<=9; i++)
		if(!check_number(date_text[i]))
			return 0;
	return 1;
}
int validation_desc()
{
	const char *desc_text=gtk_entry_get_text(GTK_ENTRY(description));
	if(strlen(desc_text)<=0)
		return 0;
	if(strlen(desc_text)>=50)
		return 0;
	return 1;
}
int get_id_file()
{
	FILE *file;
	file=fopen("id.in", "r");
	char buffer[1000];
	fgets(buffer, 100, file);
	int nr=0;
	for(int i=0; check_number(buffer[i]); i++)
		nr*=10, nr+=buffer[i]-'0';
	fclose(file);
	return nr;																																																																																				
}
void increment_id_file()
{
	int id_file=get_id_file();
	FILE *file;
	file=fopen("id.in", "w");
	fprintf(file, "%d", ++id_file);
	fclose(file);																																																																															
}
void add_transaction_in_file(const char *date_text, const char *desc_text, const char *amount_text, int option)
{
	FILE *file;
	file=fopen("transaction.in", "a");
	fprintf(file, "%d|", get_id_file()+1);
	fprintf(file, "%s|%s|%s|%d\n", date_text, desc_text, amount_text, option);
	fclose(file);
	increment_id_file();
}
void insert_data_in_file(GtkWidget *widget, gpointer *window)
{
	GtkWidget *dialog=gtk_dialog_new();
    GtkWidget *modal_area=gtk_dialog_get_content_area(GTK_DIALOG(dialog));

    gtk_window_set_title(GTK_WINDOW(dialog), "Dialog");
    gtk_window_set_transient_for(GTK_WINDOW(dialog), GTK_WINDOW(window));//aduce modal pe planul aplicatiei
   	gtk_window_set_modal(GTK_WINDOW(dialog), TRUE);//pe plan principal
    gtk_widget_set_size_request(dialog, 400, 200);
    
    GtkWidget *grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(modal_area), grid);
    
    int flag=1;
	if(!validation_date(date))
    {
    	GtkWidget *error = gtk_label_new("Date is invalid");
    	gtk_grid_attach(GTK_GRID(grid), error, 1, 1, 1, 1);
    	flag=0;
    }
    if(!validation_desc())
	{
		GtkWidget *error = gtk_label_new("Description is invalid");
    	gtk_grid_attach(GTK_GRID(grid), error, 1, 2, 1, 1);
    	flag=0;
	}
    int value_amount=transform_chars_to_integer(gtk_entry_get_text(GTK_ENTRY(amount)));
    if(value_amount==-1)
    {
    	GtkWidget *error = gtk_label_new("Amount is invalid");
    	gtk_grid_attach(GTK_GRID(grid), error, 1, 3, 1, 1);		
    	flag=0;
    }
    if(flag==1)
    {
    	const char *date_text=gtk_entry_get_text(GTK_ENTRY(date));
		const char *desc_text=gtk_entry_get_text(GTK_ENTRY(description));
		const char *amount_text=gtk_entry_get_text(GTK_ENTRY(amount));
    	GtkWidget *valid_text = gtk_label_new("Your data was recorded succesfully");
    	if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(expense)))
			add_transaction_in_file(date_text, desc_text, amount_text, 1);
		else add_transaction_in_file(date_text, desc_text, amount_text, 0);
    	gtk_grid_attach(GTK_GRID(grid), valid_text, 1, 0, 1, 1);
    	gtk_entry_set_text(GTK_ENTRY(date), "");
    	gtk_entry_set_text(GTK_ENTRY(description), "");
    	gtk_entry_set_text(GTK_ENTRY(amount), "");

    }
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_widget_show_all(dialog);
}
void show_transaction_modal(GtkWidget *widget, gpointer *window)
{
	GtkWidget *dialog=gtk_dialog_new();
    GtkWidget *modal_area=gtk_dialog_get_content_area(GTK_DIALOG(dialog));

    gtk_window_set_title(GTK_WINDOW(dialog), "Add transaction");
    gtk_window_set_transient_for(GTK_WINDOW(dialog), GTK_WINDOW(window));//aduce modal pe planul aplicatiei
   	gtk_window_set_modal(GTK_WINDOW(dialog), TRUE);//pe plan principal
    gtk_widget_set_size_request(dialog, 800, 400);
    
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 6);
    gtk_container_add(GTK_CONTAINER(modal_area), vbox);
    
    date = gtk_entry_new();
    description = gtk_entry_new();
   	amount = gtk_entry_new();
   	income = gtk_radio_button_new_with_label(NULL, "Income");
    expense = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(income), "Expense");//inclus in income
	GtkWidget *button_submit=gtk_button_new_with_label("Submit");
	
   	init_transaction_modal_entry(vbox, date, description, amount, income, expense, button_submit);
   	gtk_window_set_resizable(GTK_WINDOW(dialog), 0);
   	gtk_widget_grab_focus(income);
   	gtk_widget_set_size_request(income, 20, 20);
    gtk_widget_set_size_request(expense, 20, 20);
    gtk_widget_set_halign(vbox, GTK_ALIGN_CENTER);
    
    g_signal_connect(button_submit, "clicked", G_CALLBACK(insert_data_in_file), dialog);
    
    gtk_widget_show_all(dialog);
}
int get_sum_preprocess_all_entry()
{
	FILE *file;
	file=fopen("transaction.in", "r");
	int sum=0;
	for(int i=1; i<=get_id_file(); i++)
	{
		char buffer[105];
		fgets(buffer, 100, file);
		int j;
		for(j=0; buffer[j]!='\n'; j++);
		buffer[j]='\0';
		struct transaction element=create_transaction(buffer);
		if(element.type)
			sum-=element.amount;
		else
			sum+=element.amount;
	}
	fclose(file);
	return sum;
}
int transform_integer_to_chars(char *string, int number, int poz)
{
	if(!number && poz==0)
	{
		string[0]='0';
		string[1]='\0';
		return 1;
	}
	if(!number)
	{
		string[poz]='\0';
		return poz;
	}
	int len=transform_integer_to_chars(string, number/10, poz+1);
	string[len-poz-1]=number%10+'0';
	return len;
}
void show_balance_modal(GtkWidget *widget, gpointer *window)
{
	GtkWidget *dialog=gtk_dialog_new();
    GtkWidget *modal_area=gtk_dialog_get_content_area(GTK_DIALOG(dialog));
	char *balance_text=malloc(40);
	char *balance_value=malloc(20);
	transform_integer_to_chars(balance_value, get_sum_preprocess_all_entry(), 0);
	strcpy(balance_text, "Your balance is ");
	strcat(balance_text, balance_value);
    gtk_window_set_title(GTK_WINDOW(dialog), "Balance information");
    
    GtkWidget *information = gtk_label_new(balance_text);
    gtk_window_set_transient_for(GTK_WINDOW(dialog), GTK_WINDOW(window));//aduce modal pe planul aplicatiei
   	gtk_window_set_modal(GTK_WINDOW(dialog), TRUE);//pe plan principal
    gtk_widget_set_size_request(dialog, 400, 200);
    
    GtkWidget *grid = gtk_grid_new();
    gtk_grid_attach(GTK_GRID(grid), information, 1, 0, 1, 1);
    gtk_widget_set_size_request(information, 200, 100);
	gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_container_add(GTK_CONTAINER(modal_area), grid);
    gtk_widget_show_all(dialog);
}
enum {
    COLUMN_id,
    COLUMN_date,
    COLUMN_description,
    COLUMN_amount,
    COLUMN_type,
    NUM_COLUMNS
};

void add_row(GtkListStore *list_store, gint id, const gchar *date, const gchar *description, gint amount, const gchar *type) {
    GtkTreeIter iter;
    gtk_list_store_append(list_store, &iter);
    gtk_list_store_set(list_store, &iter, COLUMN_id, id, COLUMN_date, date, COLUMN_description, description, COLUMN_amount, amount, COLUMN_type, type, -1);
}
char *get_text(int i)
{
	char *string=malloc(50);
	if(i==0)
   		strcpy(string, "Id");
    if(i==1)
    	strcpy(string, "Date");
    if(i==2)
    	strcpy(string, "Description");
    if(i==3)
    	strcpy(string, "Amount");
    if(i==4)
    	strcpy(string, "Type");
    return string;
}
void remove_last_row(GtkWidget *tree_view) {
    GtkTreeModel *model = gtk_tree_view_get_model(GTK_TREE_VIEW(tree_view));

    // Get the number of children in the model
    gint n_children = gtk_tree_model_iter_n_children(model, NULL);

    if (n_children > 0) {
        // Get the iterator for the last row
        GtkTreeIter last_iter;
        gtk_tree_model_iter_nth_child(model, &last_iter, NULL, n_children - 1);

        // Remove the last row
        gtk_list_store_remove(GTK_LIST_STORE(model), &last_iter);
    }
}
void show_5_data_from_tabel(int page, GtkListStore *list_store)
{
	int dr=get_id_file()-5*(page-1);
	int st=dr-4;
	FILE *file;
	file=fopen("transaction.in", "r");
	struct transaction rez[10];
	int rez_len=0;
	for(int i=1; i<=get_id_file(); i++)
	{
		char buffer[105];
		fgets(buffer, 100, file);
		int j;
		for(j=0; buffer[j]!='\n'; j++);
		buffer[j]='\0';
		struct transaction element=create_transaction(buffer);
		if(element.id>=st && element.id<=dr)
			rez[++rez_len]=element;
	}
	for(int i=rez_len; i>=1; i--)
		if(rez[i].type)
			add_row(list_store, rez[i].id, rez[i].date, rez[i].description, rez[i].amount, "expense");
		else add_row(list_store, rez[i].id, rez[i].date, rez[i].description, rez[i].amount, "income");
	fclose(file);
}
char *display_pages_count(int page)
{
    char *string=malloc(50);
    strcpy(string, "  Page ");
    char *string_pages=malloc(50);
    transform_integer_to_chars(string_pages, page, 0);
    strcat(string, string_pages);
    strcat(string, "/");
    int nr=get_id_file();
    if(nr%5==0)
    	nr/=5;
    else nr=nr/5+1;
    char *string_pages_total=malloc(50);
    transform_integer_to_chars(string_pages_total, nr, 0);
    strcat(string, string_pages_total);
    strcat(string, "  ");
    return string;
}
GtkListStore *list_store;
void go_page_left(GtkWidget *widget, gpointer *tree_view)
{
	if(page==1)
		return;
	page--;
	for(int i=1; i<=5; i++)
		remove_last_row((GtkWidget*)tree_view);
	show_5_data_from_tabel(page, list_store);
	gtk_label_set_text(GTK_LABEL(page_info), display_pages_count(page));
}
void go_page_right(GtkWidget *widget, gpointer *tree_view)
{
	int nr=get_id_file();
    if(nr%5==0)
    	nr/=5;
    else nr=nr/5+1;
	if(page==nr)
		return;
	page++;
	for(int i=1; i<=5; i++)
		remove_last_row((GtkWidget*)tree_view);
	show_5_data_from_tabel(page, list_store);
	gtk_label_set_text(GTK_LABEL(page_info), display_pages_count(page));
}
void display_previous_transactions_modal(GtkWidget *widget, gpointer *window)
{
	page=1;
	GtkWidget *dialog=gtk_dialog_new();
    GtkWidget *modal_area=gtk_dialog_get_content_area(GTK_DIALOG(dialog));

    gtk_window_set_title(GTK_WINDOW(dialog), "Previous transactions");
    gtk_window_set_transient_for(GTK_WINDOW(dialog), GTK_WINDOW(window));//aduce modal pe planul aplicatiei
   	gtk_window_set_modal(GTK_WINDOW(dialog), TRUE);//pe plan principal
    gtk_widget_set_size_request(dialog, 800, 400);
    gtk_window_set_resizable(GTK_WINDOW (dialog), 0);
    list_store = gtk_list_store_new(NUM_COLUMNS, G_TYPE_INT, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_INT, G_TYPE_STRING);
    // Add some sample data
    GtkWidget *tree_view = gtk_tree_view_new_with_model(GTK_TREE_MODEL(list_store));

    for (int i = 0; i < NUM_COLUMNS; i++) {
        GtkCellRenderer *renderer = gtk_cell_renderer_text_new();
        GtkTreeViewColumn *column = gtk_tree_view_column_new_with_attributes("", renderer, "text", i, NULL);
        gtk_tree_view_column_set_title(column, get_text(i));
        gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column);
    }
    
	GtkWidget *grid = gtk_grid_new();
	gtk_grid_attach(GTK_GRID(grid), tree_view, 1, 0, 1, 1);
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    
	show_5_data_from_tabel(page, list_store);
    
    GtkWidget *grid1 = gtk_grid_new();

	GtkWidget *left_button = gtk_button_new();
    GtkWidget *left_icon = gtk_image_new_from_icon_name("go-previous", GTK_ICON_SIZE_BUTTON);  // Icon for 'go-previous'
    gtk_button_set_image(GTK_BUTTON(left_button), left_icon);
    g_signal_connect(left_button, "clicked", G_CALLBACK(go_page_left), tree_view);
    
    page_info = gtk_label_new(display_pages_count(page));
    
    GtkWidget *right_button = gtk_button_new();
    GtkWidget *right_icon = gtk_image_new_from_icon_name("go-next", GTK_ICON_SIZE_BUTTON);  // Icon for 'go-previous'
    g_signal_connect(right_button, "clicked", G_CALLBACK(go_page_right), tree_view);
    gtk_button_set_image(GTK_BUTTON(right_button), right_icon);
    
    gtk_grid_attach(GTK_GRID(grid1), left_button, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid1), page_info, 2, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid1), right_button, 3, 0, 1, 1);
	gtk_widget_set_halign(grid1, GTK_ALIGN_CENTER);
    gtk_box_pack_start(GTK_BOX(box), grid, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(box), grid1, TRUE, TRUE, 0);
    gtk_container_add(GTK_CONTAINER(modal_area), box);
    gtk_widget_show_all(dialog);
}
GtkWidget *start_date, *end_date;
char *get_year_from_date(const char *date)
{
	char *year=malloc(10);
	for(int i=0; i<=3; i++)
		year[i]=date[6+i];
	year[4]='\0';
	return year;
}
char *get_month_from_date(const char *date)
{
	char *month=malloc(10);
	for(int i=0; i<=1; i++)
		month[i]=date[3+i];
	month[2]='\0';
	return month;
}
char *get_day_from_date(const char *date)
{
	char *day=malloc(10);
	for(int i=0; i<=1; i++)
		day[i]=date[i];
	day[2]='\0';
	return day;
}
int compare_date(const char *date1, const char *date2)///return 1 if date1<date2
{
	if(transform_chars_to_integer(get_year_from_date(date1))>transform_chars_to_integer(get_year_from_date(date2)))
		return 0;
	if(transform_chars_to_integer(get_year_from_date(date1))<transform_chars_to_integer(get_year_from_date(date2)))
		return 1;
		
	if(transform_chars_to_integer(get_month_from_date(date1))>transform_chars_to_integer(get_month_from_date(date2)))
		return 0;
	if(transform_chars_to_integer(get_month_from_date(date1))<transform_chars_to_integer(get_month_from_date(date2)))
		return 1;
		
	if(transform_chars_to_integer(get_day_from_date(date1))>transform_chars_to_integer(get_day_from_date(date2)))
		return 0;
	return 1;
}
int calculate_period(const char *date1, const char *date2, int type)
{
	FILE *file;
	file=fopen("transaction.in", "r");
	struct transaction rez[10];
	int rez_len=0;
	int sum_total=0;
	for(int i=1; i<=get_id_file(); i++)
	{
		char buffer[105];
		fgets(buffer, 100, file);
		int j;
		for(j=0; buffer[j]!='\n'; j++);
		buffer[j]='\0';
		struct transaction element=create_transaction(buffer);
		if(compare_date(date1, element.date) && compare_date(element.date, date2))//date1<=element.date && element.date<=date2
			if(type==0 && element.type==0)
				sum_total+=element.amount;
			else if(type==1 && element.type==1)
				sum_total+=element.amount;
	}
	return sum_total;
}
void financial_report_modal(GtkWidget *widget, gpointer *window)
{
	GtkWidget *dialog=gtk_dialog_new();
    GtkWidget *modal_area=gtk_dialog_get_content_area(GTK_DIALOG(dialog));
    gtk_window_set_title(GTK_WINDOW(dialog), "Dialog");
    gtk_window_set_transient_for(GTK_WINDOW(dialog), GTK_WINDOW(window));//aduce modal pe planul aplicatiei
   	gtk_window_set_modal(GTK_WINDOW(dialog), TRUE);//pe plan principal
    gtk_widget_set_size_request(dialog, 800, 400);
    gtk_window_set_resizable(GTK_WINDOW (dialog), 0);
    
    GtkWidget *grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(modal_area), grid);
    
    int flag=1;
	if(!validation_date(start_date))
    {
    	GtkWidget *error = gtk_label_new("Start date is invalid");
    	gtk_grid_attach(GTK_GRID(grid), error, 1, 0, 1, 1);
    	flag=0;
    }
    if(!validation_date(end_date))
    {
    	GtkWidget *error = gtk_label_new("End date is invalid");
    	gtk_grid_attach(GTK_GRID(grid), error, 1, 1, 1, 1);
    	flag=0;
    }
    if(flag)
    {
    	const char *start_date_text=gtk_entry_get_text(GTK_ENTRY(start_date));
    	const char *end_date_text=gtk_entry_get_text(GTK_ENTRY(end_date));
   		if(compare_date(start_date_text, end_date_text))
   		{
   			char *income_print=malloc(100);
   			strcpy(income_print, "Your incomes between ");
   			strcat(income_print, start_date_text);
   			strcat(income_print, " and ");
   			strcat(income_print, end_date_text);
   			strcat(income_print, " is:");
   			char *income_val_text=malloc(50);
   			transform_integer_to_chars(income_val_text, calculate_period(start_date_text, end_date_text, 0), 0);
   			strcat(income_print, income_val_text);
			GtkWidget *income_label = gtk_label_new(income_print);
			
			char *expenses_print=malloc(100);
   			strcpy(expenses_print, "Your expenses between ");
   			strcat(expenses_print, start_date_text);
   			strcat(expenses_print, " and ");
   			strcat(expenses_print, end_date_text);
   			strcat(expenses_print, " is: ");
   			char *expenses_val_text=malloc(50);
   			transform_integer_to_chars(expenses_val_text, calculate_period(start_date_text, end_date_text, 1), 0);
   			strcat(expenses_print, expenses_val_text);

			GtkWidget *expense_label = gtk_label_new(expenses_print);
			gtk_grid_attach(GTK_GRID(grid), income_label, 1, 0, 1, 1);
			gtk_grid_attach(GTK_GRID(grid), expense_label, 1, 1, 1, 1);
		}
		else
		{
			GtkWidget *error = gtk_label_new("Logic error");
    		gtk_grid_attach(GTK_GRID(grid), error, 1, 1, 1, 1);
    	}
		
    }
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_widget_show_all(dialog);
}
void display_financial_report(GtkWidget *widget, gpointer *window)
{
	GtkWidget *dialog=gtk_dialog_new();
    GtkWidget *modal_area=gtk_dialog_get_content_area(GTK_DIALOG(dialog));
    gtk_window_set_title(GTK_WINDOW(dialog), "Financial report");
    gtk_window_set_transient_for(GTK_WINDOW(dialog), GTK_WINDOW(window));//aduce modal pe planul aplicatiei
   	gtk_window_set_modal(GTK_WINDOW(dialog), TRUE);//pe plan principal
    gtk_widget_set_size_request(dialog, 800, 400);
    gtk_window_set_resizable(GTK_WINDOW (dialog), 0);
	
	GtkWidget *grid = gtk_grid_new();
	gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
	
	start_date=gtk_entry_new();
    end_date=gtk_entry_new();
    gtk_widget_set_size_request(start_date, 205, 40);
	gtk_entry_set_placeholder_text(GTK_ENTRY(start_date), "Start date:(dd.mm.yyyy)");//place holder
    gtk_widget_set_size_request(end_date, 205, 40);
	gtk_entry_set_placeholder_text(GTK_ENTRY(end_date), "End date:(dd.mm.yyyy)");//place holder
	
	gtk_grid_attach(GTK_GRID(grid), start_date, 0, 1, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), end_date, 0, 2, 1, 1);
	
	GtkWidget *generate_report_button = gtk_button_new_with_label("Generate report");
	gtk_grid_attach(GTK_GRID(grid), generate_report_button, 0, 3, 1, 1);
	g_signal_connect(generate_report_button, "clicked", G_CALLBACK(financial_report_modal), dialog);
	gtk_container_add(GTK_CONTAINER(modal_area), grid);
	gtk_widget_show_all(dialog);
}
int main(int argc, char *argv[]) {
	
    gtk_init(&argc, &argv);
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    init_window(window);
    
    GtkWidget *add_transaction_button = gtk_button_new_with_label("Add transaction");
    g_signal_connect(add_transaction_button, "clicked", G_CALLBACK(show_transaction_modal), window);
    
    GtkWidget *show_balance = gtk_button_new_with_label("Show balance");
   	g_signal_connect(show_balance, "clicked", G_CALLBACK(show_balance_modal), window);
    
    GtkWidget *display_previous_transactions = gtk_button_new_with_label("Display previous transactions");
    g_signal_connect(display_previous_transactions, "clicked", G_CALLBACK(display_previous_transactions_modal), window);
    
	GtkWidget *financial_report = gtk_button_new_with_label("Financial report");
	g_signal_connect(financial_report, "clicked", G_CALLBACK(display_financial_report), window);
	
    GtkWidget *grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);
    
	init_grid(grid, add_transaction_button, show_balance, display_previous_transactions, financial_report);
	
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_widget_show_all(window);
    gtk_main();
    return 0;
}
