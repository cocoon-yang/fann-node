/*
 * ynodefanntraindata.cpp
 *
 *  Created on: 2017Äê4ÔÂ22ÈÕ
 *      Author: GW00121076
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

	NODE_SET_PROTOTYPE_METHOD(tpl, "set_train_data", set_train_data);
	NODE_SET_PROTOTYPE_METHOD(tpl, "read_train_from_file", read_train_from_file);

	NODE_SET_PROTOTYPE_METHOD(tpl, "scale_train_data", scale_train_data);

	NODE_SET_PROTOTYPE_METHOD(tpl, "scale_input_train_data", scale_input_train_data);
	NODE_SET_PROTOTYPE_METHOD(tpl, "scale_output_train_data", scale_output_train_data);


	NODE_SET_PROTOTYPE_METHOD(tpl, "destroy", destroy);
	NODE_SET_PROTOTYPE_METHOD(tpl, "save", save);

	//NODE_SET_PROTOTYPE_METHOD(tpl, "length_train_data", length_train_data);



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



//
// void set_train_data(unsigned int num_data,
//    unsigned int num_input, fann_type **input,
//    unsigned int num_output, fann_type **output)
//
void YNodeFANNTrainData::set_train_data( const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = args.GetIsolate();
	YNodeFANNTrainData* obj = ObjectWrap::Unwrap<YNodeFANNTrainData>(args.Holder());

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
								"one argument is an undefined value.")));
		return;
	}

	v8::Handle<v8::Array> dataArray;
	if (args[0]->IsArray())
	{
		dataArray = v8::Handle<v8::Array>::Cast(args[0]);
	}else	{
		isolate->ThrowException(
				v8::Exception::TypeError(
						String::NewFromUtf8(isolate,
								"argument is NOT an array.")));
		return;
	}

	unsigned int num_data = dataArray->Length();
	unsigned int num_input;
	unsigned int num_output;

	v8::Handle<v8::Value> tmp_arrayItem = dataArray->Get(
					v8::Int32::New(isolate, 0));
	v8::Handle<v8::Array> tmp_itemArray = v8::Handle<v8::Array>::Cast(tmp_arrayItem);
	v8::Handle<v8::Value> tmp_inputItem = tmp_itemArray->Get(
					v8::Int32::New(isolate, 0));
	v8::Handle<v8::Value> tmp_outputItem = tmp_itemArray->Get(
							v8::Int32::New(isolate, 1));
	num_input = v8::Handle<v8::Array>::Cast(tmp_inputItem)->Length();
	num_output = v8::Handle<v8::Array>::Cast(tmp_outputItem)->Length();

	struct fann_train_data *data =
	                (struct fann_train_data *)malloc(sizeof(struct fann_train_data));
	if( NULL == data )
	{
		free(data);
		data = NULL;
		isolate->ThrowException(
				v8::Exception::TypeError(
						String::NewFromUtf8(isolate,
								"allocating memory failed.")));
		return;
	}

    data->num_data = num_data;
    data->num_input = num_input;
    data->num_output = num_output;
	data->input  = NULL;
	data->output  = NULL;

	fann_type *data_input = (fann_type *)calloc(num_input*num_data, sizeof(fann_type));
	fann_type *data_output = (fann_type *)calloc(num_output*num_data, sizeof(fann_type));

	if( ( NULL == data_input ) || ( NULL == data_output )  )
	{
		free(data);
		data = NULL;
		free(data_input);
		data_input = NULL;
		free(data_output);
		data_output = NULL;

		isolate->ThrowException(
				v8::Exception::TypeError(
						String::NewFromUtf8(isolate,
								"allocating memory failed.")));
		return;
	}

	data->input = &data_input;
	data->output = &data_output;

	for (int i = 0; i < num_data; i++)
	{
		v8::Handle<v8::Value> arrayItem = dataArray->Get(
				v8::Int32::New(isolate, i));

		if ( !arrayItem->IsArray())
		{
			free(data);
			data = NULL;
			free(data_input);
			data_input = NULL;
			free(data_output);
			data_output = NULL;
			isolate->ThrowException(
					v8::Exception::TypeError(
							String::NewFromUtf8(isolate,
									"argument is NOT an array.")));
			return;
		}

		v8::Handle<v8::Array> itemArray = v8::Handle<v8::Array>::Cast(arrayItem);
		v8::Handle<v8::Value> inputItem = itemArray->Get(
						v8::Int32::New(isolate, 0));
		v8::Handle<v8::Value> outputItem = itemArray->Get(
								v8::Int32::New(isolate, 1));

		if ( ( !inputItem->IsArray() ) || ( !outputItem->IsArray()  )  )
		{
			free(data);
			data = NULL;
			free(data_input);
			data_input = NULL;
			free(data_output);
			data_output = NULL;
			isolate->ThrowException(
					v8::Exception::TypeError(
							String::NewFromUtf8(isolate,
									"argument is NOT an array.")));
			return;
		}

		v8::Handle<v8::Array> inputArray = v8::Handle<v8::Array>::Cast(inputItem);
		v8::Handle<v8::Array> outputArray = v8::Handle<v8::Array>::Cast(outputItem);

		for (int j = 0; j < num_input; j++)
		{
			v8::Handle<v8::Value> theItem = inputArray->Get(
							v8::Int32::New(isolate, j));
			data_input[j] = theItem->NumberValue();

		}
		data_input += num_input;

		for (int j = 0; j < num_output; j++)
		{
			v8::Handle<v8::Value> theItem = outputArray->Get(
							v8::Int32::New(isolate, j));
			data_output[j] = theItem->NumberValue();
		}
		data_output += num_output;
	}
    if (obj->train_data != NULL)
    {
        fann_destroy_train(obj->train_data);
        obj->train_data = NULL;
    }
	obj->train_data = data;
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
