SRC_DIR := ./src
INC_DIR := ./inc
OUT_DIR := ./out

CC := gcc
C_VERSION := 99
CFLAGS := -std=c$(C_VERSION) -Wall -Werror -pedantic -I$(INC_DIR)

FTESTS_DIR := ./func_tests/scripts
UTESTS_DIR := ./unit_tests

OBJS_ALL :=  $(OUT_DIR)/stack_oper.o $(OUT_DIR)/show_error.o 
OBJS_MAIN := $(OUT_DIR)/main.o

app.exe: $(OBJS_MAIN) $(OBJS_ALL)
	@$(CC) -o $@ $^

$(OUT_DIR)/%.o: $(SRC_DIR)/%.c $(INC_DIR)/*.h object_dir
	@$(CC) $(CFLAGS) -c $< -o $@

.PHONY: func clean object_dir

object_dir:
	@mkdir -p $(OUT_DIR)

clean:
	@$(RM) ./*.exe
	@$(RM) $(OUT_DIR)/*.o $(OUT_DIR)/*.gcda $(OUT_DIR)/*.gcno $(OUT_DIR)/*.c.gcov $(OUT_DIR)/*.out
	@$(RM) $(FTESTS_DIR)/program_out.txt
	@rm -rf $(OUT_DIR)
