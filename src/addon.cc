

// addon.cc
#include <node.h>
#include "ynodefann.h"
#include "ynodefanntraindata.h"
//namespace demo {

using v8::Local;
using v8::Object;

void InitAll(Local<Object> exports) {
	YNodeFANN::Init(exports);
	YNodeFANNTrainData::Init(exports);
}

NODE_MODULE(bdfparser, InitAll)

