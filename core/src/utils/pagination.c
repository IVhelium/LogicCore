#include <stddef.h>
#include "utils/pagination.h"

static void pagination_update(Pagination *pagination);


bool pagination_create(Pagination *pagination, int page, int page_size, int item_count)
{
    if (pagination == NULL) return false;
    if (page_size <= 0) return false;
    
    pagination->page = page;
    pagination->page_size = page_size;
    pagination->item_count = item_count;
    pagination->total_pages = (item_count + page_size - 1) / page_size;
    pagination->start = page * page_size;
    pagination->end = pagination->start + page_size;

    if (page < 0 || page >= pagination->total_pages) return false;
    if (pagination->end > item_count) pagination->end = item_count; 

    return true;
}

bool pagination_next(Pagination *pagination)
{
    if (pagination->page + 1 < pagination->total_pages) pagination->page++;
    pagination_update(pagination);

    return true;
}

bool pagination_previous(Pagination *pagination)
{
    if (pagination->page > 0) pagination->page--;
    pagination_update(pagination);

    return true;
}

static void pagination_update(Pagination *pagination)
{
    if (pagination == NULL) return;

    pagination->total_pages = (pagination->item_count + pagination->page_size - 1) / pagination->page_size;
    pagination->start = pagination->page * pagination->page_size;
    pagination->end = pagination->start + pagination->page_size;

    if (pagination->end > pagination->item_count) pagination->end = pagination->item_count;
}