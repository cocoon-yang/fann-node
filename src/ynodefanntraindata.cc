/*
 * ynodefanntraindata.cpp
 *
 *  Created on: April, 2017
 *      Author: Chunfeng Yang
 */

#include "ynodefanntraindata.h"

using v8::Function;
using v8::FunctionCallbackInfo;
using v8::FunctionTemplate;
using v8::Isolate;
using v8::Local;
using v8::Number;
using v8::Object;
using v8::Persistent;
using v8::String;
using v8::Value;
using v8::Array;


Persistent<Function> YNodeFANNTrainData::constructor;

YNodeFANNTrainData::YNodeFANNTrainData() {
	train_data = NULL;
}

YNodeFANNTrainData::~YNodeFANNTrainData() {
    if (train_data != NULL)
    {
        fann_destroy_train(train_data);
        train_data = NULL;
    }
}

void YNodeFANNTrainData::Init(Local<Object> exports) {
	Isolate* isolate = exports->GetIsolate();

	// Prepare constructor template
	Local < FunctionTemplate > tpl = FunctionTemplate::New(isolate, New);
	tpl->SetClassName(String::NewFromUtf8(isolate, "YNodeFANNTrainData"));
	tpl->InstanceTemplate()->SetInternalFieldCount(1);

	//
	NODE_SET_PROTOTYPE_METHOD(tpl, "num_input_train_data", num_input_train_data);
	NODE_SET_PROTOTYPE_METHOD(tpl, "num_output_train_data", num_output_train_data);
	NODE_SET_PROTOTYPE_METHOD(tpl, "length_train_data", length_train_data);

	NODE_SET_PROTOTYPE_METHOD(tpl, "read_train_from_file", read_train_from_file);

	NODE_SET_PROTOTYPE_METHOD(tpl, "scale_train_data", scale_train_data);

	NODE_SET_PROTOTYPE_METHOD(tpl, "scale_input_train_data", scale_input_train_data);
	NODE_SET_PROTOTYPE_METHOD(tpl, "scale_output_train_data", scale_output_train_data);


	NODE_SET_PROTOTYPE_METHOD(tpl, "destroy", destroy);
	NODE_SET_PROTOTYPE_METHOD(tpl, "save", save);

	constructor.Reset(isolate, tpl->GetFunction());
	exports->Set(String::NewFromUtf8(isolate, "YNodeFANNTrainData"), tpl->GetFunction());
}


void YNodeFANNTrainData::New(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = args.GetIsolate();

	if (args.IsConstructCall()) {
		// Invoked as constructor: `new YBDFParser(...)`
		//double value = args[0]->IsUndefined() ? 0 : args[0]->NumberValue();
		YNodeFANNTrainData* obj = new YNodeFANNTrainData();
		obj->Wrap(args.This());
		args.GetReturnValue().Set(args.This());
	} else {
		// Invoked as plain function `YBDFParser(...)`, turn into construct call.
		const int argc = 1;
		Local<Value> argv[argc] =
		{	args[0]};
		Local < Function > cons = Local < Function
				> ::New(isolate, constructor);
		args.GetReturnValue().Set(cons->NewInstance(argc, argv));
	}
	return;
}


void YNodeFANNTrainData::read_train_from_file( const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = args.GetIsolate();
	YNodeFANNTrainData* obj = ObjectWrap::Unwrap<YNodeFANNTrainData>(args.Holder());

    // checking arguments number
    if (args.Length() < 1)
    {
        isolate->ThrowException(
                    v8::Exception::TypeError(
                        String::NewFromUtf8(isolate, "Wrong arguments number")));
        return;
    }
    // checking arguments
    if( args[0]->IsUndefined())
    {
        isolate->ThrowException(
                     v8::Exception::TypeError(
                         String::NewFromUtf8(isolate, "The first argument undefined.")));
        return;
    }
	if (args[0]->IsString())
	{
		char *name;
		v8::String::Utf8Value str(args[0]->ToString());
		name = *str;
		if (NULL == obj->train_data)
		{
			obj->train_data = fann_read_train_from_file(name);
		}else{
			fann_destroy_train(obj->train_data);
			obj->train_data = NULL;
			obj->train_data = fann_read_train_from_file(name);
		}
	}else     {
        isolate->ThrowException(
                     v8::Exception::TypeError(
                         String::NewFromUtf8(isolate, "The first argument is NOT a string.")));
        return;
    }

}


void YNodeFANNTrainData::save(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = args.GetIsolate();
	YNodeFANNTrainData* obj = ObjectWrap::Unwrap<YNodeFANNTrainData>(
			args.Holder());

	// checking arguments number
	if (args.Length() < 1)
	{
		isolate->ThrowException(
				v8::Exception::TypeError(
						String::NewFromUtf8(isolate,
								"Wrong arguments number")));
		return;
	}
	// checking arguments
	if (args[0]->IsUndefined())
	{
		isolate->ThrowException(
				v8::Exception::TypeError(
						String::NewFromUtf8(isolate,
								"The first argument undefined.")));
		return;
	}
	if (args[0]->IsString())
	{
		char *name;
		v8::String::Utf8Value str(args[0]->ToString());
		name = *str;
		if (NULL == obj->train_data)
		{
			return;
		}
		else
		{
			if (fann_save_train(obj->train_data, name) == -1)
			{
				isolate->ThrowException(
						v8::Exception::TypeError(
								String::NewFromUtf8(isolate,
										"Save train data failed.")));
				return;
			}

		}
	}
	else
	{
		isolate->ThrowException(
				v8::Exception::TypeError(
						String::NewFromUtf8(isolate,
								"The first argument is NOT a string.")));
		return;
	}
}

void YNodeFANNTrainData::length_train_data(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = args.GetIsolate();
	YNodeFANNTrainData* obj = ObjectWrap::Unwrap<YNodeFANNTrainData>(args.Holder());

	int number = 0;
    if (obj->train_data == NULL)
    {
        return;
    }
    else
    {
    	number = fann_length_train_data(obj->train_data);
    }

    args.GetReturnValue().Set(v8::Int32::New(isolate, number ));
    return ;
}

void YNodeFANNTrainData::num_input_train_data(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = args.GetIsolate();
	YNodeFANNTrainData* obj = ObjectWrap::Unwrap<YNodeFANNTrainData>(args.Holder());

	int number = 0;
    if (obj->train_data == NULL)
    {
        return;
    }
    else
    {
    	number = fann_num_input_train_data(obj->train_data);
    }

    args.GetReturnValue().Set(v8::Int32::New(isolate, number ));
    return ;
}

void YNodeFANNTrainData::num_output_train_data(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = args.GetIsolate();
	YNodeFANNTrainData* obj = ObjectWrap::Unwrap<YNodeFANNTrainData>(args.Holder());

	int number = 0;
    if (obj->train_data == NULL)
    {
        return;
    }
    else
    {
    	number = fann_num_output_train_data(obj->train_data);
    }

    args.GetReturnValue().Set(v8::Int32::New(isolate, number ));
    return ;
}


void YNodeFANNTrainData::scale_input_train_data( const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = args.GetIsolate();
	YNodeFANNTrainData* obj = ObjectWrap::Unwrap<YNodeFANNTrainData>( args.Holder());

	// checking arguments number
	if (args.Length() < 2)
	{
		isolate->ThrowException(
				v8::Exception::TypeError(
						String::NewFromUtf8(isolate,
								"Wrong arguments number")));
		return;
	}
	// checking arguments

	float min = args[0]->IsUndefined() ? 0.0 : args[0]->NumberValue();
	float max = args[1]->IsUndefined() ? 0.0 : args[1]->NumberValue();

	if (obj->train_data != NULL)
	{
		fann_scale_input_train_data(obj->train_data, min, max);
	}
}

void YNodeFANNTrainData::scale_output_train_data( const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = args.GetIsolate();
	YNodeFANNTrainData* obj = ObjectWrap::Unwrap<YNodeFANNTrainData>(args.Holder());

	// checking arguments number
	if (args.Length() < 2)
	{
		isolate->ThrowException(
				v8::Exception::TypeError(
						String::NewFromUtf8(isolate,
								"Wrong arguments number")));
		return;
	}
	// checking arguments

	float min = args[0]->IsUndefined() ? 0.0 : args[0]->NumberValue();
	float max = args[1]->IsUndefined() ? 0.0 : args[1]->NumberValue();

	if (obj->train_data != NULL)
	{
		fann_scale_output_train_data(obj->train_data, min, max);
	}
}


void YNodeFANNTrainData::scale_train_data( const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = args.GetIsolate();
	YNodeFANNTrainData* obj = ObjectWrap::Unwrap<YNodeFANNTrainData>(args.Holder());

	// checking arguments number
	if (args.Length() < 2)
	{
		isolate->ThrowException(
				v8::Exception::TypeError(
						String::NewFromUtf8(isolate,
								"Wrong arguments number")));
		return;
	}
	// checking arguments

	float min = args[0]->IsUndefined() ? 0.0 : args[0]->NumberValue();
	float max = args[1]->IsUndefined() ? 0.0 : args[1]->NumberValue();

	if (obj->train_data != NULL)
	{
		fann_scale_train_data(obj->train_data, min, max);
	}
}


void YNodeFANNTrainData::destroy(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = args.GetIsolate();
	YNodeFANNTrainData* obj = ObjectWrap::Unwrap<YNodeFANNTrainData>(args.Holder());
	if (obj->train_data != NULL)
	{
		fann_destroy_train(obj->train_data);
		obj->train_data = NULL;
	}
}
