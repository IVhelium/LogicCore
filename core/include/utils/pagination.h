#pragma once

typedef struct
{
    int page;
    int page_size;
    int item_count;
    int total_pages;
    int start;
    int end;
} Pagination;


bool pagination_create(
    Pagination *pagination,
    int page,
    int page_size,
    int item_count
);

bool pagination_next(Pagination *pagination);
bool pagination_previous(Pagination *pagination);