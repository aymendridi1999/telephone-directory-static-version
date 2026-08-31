CC ?= gcc
CFLAGS ?= -std=c11 -Wall -Wextra -Wpedantic

TARGET = contact
TEST_TARGET = test_contact

all: $(TARGET)

$(TARGET): main.c contact.c contact.h
	$(CC) $(CFLAGS) main.c contact.c -o $(TARGET)

test: $(TEST_TARGET)
	./$(TEST_TARGET)

$(TEST_TARGET): test_contact.c contact.c contact.h
	$(CC) $(CFLAGS) test_contact.c contact.c -o $(TEST_TARGET)

clean:
	rm -f $(TARGET) $(TEST_TARGET) *.o

.PHONY: all test clean
