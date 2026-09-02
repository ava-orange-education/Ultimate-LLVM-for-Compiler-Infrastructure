// Listing 12-46. Declaring a subtarget feature
// Run: llvm-tblgen --print-records -I $LLVM_DIR/include -I . listing-12-46.td -o /dev/null

include "MyArchCallingConv.td"

// A feature carries four strings: the name used on the command line, the C++
// field it sets in the Subtarget class, the value to set it to, and a
// description for -mattr=help. An optional fifth argument lists features it
// implies.
def FeatureMul : SubtargetFeature<"mul", "HasMul", "true",
                                  "Has a hardware multiplier">;

// Processors are declared with Processor or ProcessorModel -- the latter also
// names a scheduling model. NoSchedModel is the placeholder used until the
// target has a real one.
def : ProcessorModel<"generic",   NoSchedModel, []>;
def : ProcessorModel<"myarch1",   NoSchedModel, [FeatureMul]>;
