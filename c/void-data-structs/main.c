#include <stdio.h>

#include "array.h"

int main()
{
    Array a;
    array_init(&a, sizeof(float), 10);

    for (float i = 0; i < 20; i++)
        array_push(&a, &(float){ i * 2 });

    for (int i = 0; i < a.size; i++) {
        float *value = array_get(&a, i);
        if (!value)
            continue;
        printf("%d: %f\n", i, *value);
    }

    array_free(&a);
    return 0;
}
