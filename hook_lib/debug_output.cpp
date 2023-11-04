#include "debug_output.h"
#include "Main.hpp"
#include "game_inc.h"
#include "addr_utils.hpp"

FILE* debug_file;

void debug_output(const char* buf)
{
    if (gameInitialized == true)
    {
        if (Dvar_GetBoolSafe("print_debug"))
        {
            printf(buf);
            if (debug_file != NULL)
            {
                fprintf(debug_file, buf);
            }
        }
    }
}

utils::hook::detour com_printmessageinternal;
void Com_PrintMessageInternal_Detour(int channel, const char* text, int param_3)
{
    debug_output(text);
    com_printmessageinternal.stub<void>(channel, text, param_3);
}

void debug_output_init(const char* output_file) {
    if (output_file != NULL) debug_file = fopen(output_file, "w+");

    com_printmessageinternal.create(0x1412B0660_g, Com_PrintMessageInternal_Detour);
}