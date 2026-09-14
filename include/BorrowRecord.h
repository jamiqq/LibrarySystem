#pragma once
#include <Member.h>
#include <Item.h>
#include "Date.h"

struct BorrowRecord {
    int itemId;
    int memberId;
    Date borrowDate;
    Date dueDate;
    bool returned;

    BorrowRecord(int itemId, int memberId);
    ~BorrowRecord();

    bool checkIsReturned() const;
};