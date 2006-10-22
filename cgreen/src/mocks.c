#include "mocks.h"
#include "reporter.h"
#include "vector.h"
#include <stdlib.h>

enum {playing = 1, recording};
static int record_state = playing;
static int should_keep = 0;

typedef struct _RecordedResult {
    const char *function;
    intptr_t result;
    int should_keep;
} RecordedResult;

static Vector *result_queue = NULL;

void _checked_integer(const char *file, int line, const char *parameter, int integer) {
}

void _checked_string(const char *file, int line, const char *parameter, int string) {
}

void _checked_address(const char *file, int line, const char *parameter, int address) {
}

intptr_t _stubbed_result(const char *function, const char *file, int line) {
    int i;
    for (i = 0; i < vector_size(result_queue); i++) {
        RecordedResult *record = vector_get(result_queue, i);
        if (record->function == function) {
            intptr_t result = record->result;
            if (! record->should_keep) {
                free(vector_remove(result_queue, i));
            }
            return result;
        }
    }
    (*get_test_reporter()->assert_true)(
            get_test_reporter(),
            file,
            line,
            0,
            "No return value set for function [%s]",
            function);
}

void _expect(const char *function, const char *file, int line) {
    record_state = recording;
}

void _mock(const char *function, const char *file, int line) {
    record_state = recording;
}

void _play() {
    record_state = playing;
    should_keep = 0;
}

void _will_return(const char *function, intptr_t result) {
    if (result_queue== NULL) {
        result_queue = create_vector(&free);
    }
    RecordedResult *record = (RecordedResult *)malloc(sizeof(RecordedResult));
    record->function = function;
    record->result = result;
    record->should_keep = should_keep;
    vector_add(result_queue, record);
}

void _mask(const char *parameters) {
}

void _always() {
    should_keep = 1;
}

void clear_mocks() {
    if (result_queue != NULL) {
        destroy_vector(result_queue);
    }
}

void tally_mocks(TestReporter *reporter) {
    clear_mocks();
}
