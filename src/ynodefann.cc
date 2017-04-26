/*
 * ynodefann.cpp
 *
 *  Created on: April, 2017
 *      Author: Chunfeng Yang
 */

#include "ynodefann.h"
#include "ynodefanntraindata.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

Persistent<Function> YNodeFANN::constructor;

YNodeFANN::YNodeFANN()
{
	ann = NULL;
}

YNodeFANN::~YNodeFANN()
{
	if (ann != NULL)
	{
//        user_context *user_data = static_cast<user_context *>(fann_get_user_data(obj->ann));
//        if (user_data != NULL)
//            delete user_data;

		fann_destroy(ann);
		ann = NULL;
	}
}

void YNodeFANN::Init(Local<Object> exports)
{
	Isolate* isolate = exports->GetIsolate();

	// Prepare constructor template
	Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
	tpl->SetClassName(String::NewFromUtf8(isolate, "YNodeFANN"));
	tpl->InstanceTemplate()->SetInternalFieldCount(1);

	NODE_SET_PROTOTYPE_METHOD(tpl, "create_from_file", create_from_file);
	NODE_SET_PROTOTYPE_METHOD(tpl, "create_standard_array", create_standard_array);
	NODE_SET_PROTOTYPE_METHOD(tpl, "create_shortcut_array", create_shortcut_array);
	NODE_SET_PROTOTYPE_METHOD(tpl, "create_sparse_array", create_sparse_array);

	NODE_SET_PROTOTYPE_METHOD(tpl, "destroy", destroy);

	NODE_SET_PROTOTYPE_METHOD(tpl, "set_training_algorithm", set_training_algorithm);
	NODE_SET_PROTOTYPE_METHOD(tpl, "set_activation_function_hidden", set_activation_function_hidden);
	NODE_SET_PROTOTYPE_METHOD(tpl, "set_activation_function_output", set_activation_function_output);
	NODE_SET_PROTOTYPE_METHOD(tpl, "set_train_error_function", set_train_error_function);

	NODE_SET_PROTOTYPE_METHOD(tpl, "set_activation_steepness", set_activation_steepness);
	NODE_SET_PROTOTYPE_METHOD(tpl, "set_activation_steepness_layer", set_activation_steepness_layer);
	NODE_SET_PROTOTYPE_METHOD(tpl, "set_activation_steepness_hidden", set_activation_steepness_hidden);
	NODE_SET_PROTOTYPE_METHOD(tpl, "set_activation_steepness_output", set_activation_steepness_output);
	NODE_SET_PROTOTYPE_METHOD(tpl, "set_cascade_activation_steepnesses", set_cascade_activation_steepnesses);
	NODE_SET_PROTOTYPE_METHOD(tpl, "set_weight", set_weight);
	NODE_SET_PROTOTYPE_METHOD(tpl, "set_learning_momentum", set_learning_momentum );
	NODE_SET_PROTOTYPE_METHOD(tpl, "set_learning_rate", set_learning_rate );

	NODE_SET_PROTOTYPE_METHOD(tpl, "get_learning_rate", get_learning_rate );
	NODE_SET_PROTOTYPE_METHOD(tpl, "get_num_input", get_num_input);
	NODE_SET_PROTOTYPE_METHOD(tpl, "get_num_output", get_num_output);
	NODE_SET_PROTOTYPE_METHOD(tpl, "get_MSE", get_MSE);

	NODE_SET_PROTOTYPE_METHOD(tpl, "test", test);
	NODE_SET_PROTOTYPE_METHOD(tpl, "test_data", test_data);
	NODE_SET_PROTOTYPE_METHOD(tpl, "train_on_data", train_on_data );
	NODE_SET_PROTOTYPE_METHOD(tpl, "run", run);

	NODE_SET_PROTOTYPE_METHOD(tpl, "save", save);
	NODE_SET_PROTOTYPE_METHOD(tpl, "print_connections", print_connections );

	constructor.Reset(isolate, tpl->GetFunction());
	exports->Set(String::NewFromUtf8(isolate, "YNodeFANN"), tpl->GetFunction());

}

void YNodeFANN::New(const FunctionCallbackInfo<Value>& args)
{
	Isolate* isolate = args.GetIsolate();

	if (args.IsConstructCall())
	{
		// Invoked as constructor: `new YBDFParser(...)`
		//double value = args[0]->IsUndefined() ? 0 : args[0]->NumberValue();
		YNodeFANN* obj = new YNodeFANN();
		obj->Wrap(args.This());
		args.GetReturnValue().Set(args.This());
	}
	else
	{
		// Invoked as plain function `YBDFParser(...)`, turn into construct call.
		const int argc = 1;
		Local<Value> argv[argc] =
		{ args[0] };
		Local<Function> cons = Local<Function>::New(isolate, constructor);
		args.GetReturnValue().Set(cons->NewInstance(argc, argv));
	}
	return;
}

void YNodeFANN::set_training_algorithm(
		const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = args.GetIsolate();
	YNodeFANN* obj = ObjectWrap::Unwrap<YNodeFANN>(args.Holder());

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
	int algo_id = args[0]->IsUndefined() ? 0 : args[0]->Int32Value();

	if (obj->ann != NULL)
	{
		fann_set_training_algorithm(obj->ann,
				static_cast<fann_train_enum>(algo_id));
	}
	else
	{
		isolate->ThrowException(
				v8::Exception::TypeError(
						String::NewFromUtf8(isolate, "ann pointer is NULL")));
		return;
	}

}
void YNodeFANN::set_activation_function_hidden(
		const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = args.GetIsolate();
	YNodeFANN* obj = ObjectWrap::Unwrap<YNodeFANN>(args.Holder());

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
	int algo_id = args[0]->IsUndefined() ? 0 : args[0]->Int32Value();

	if (obj->ann != NULL)
	{
		fann_set_activation_function_hidden(obj->ann,
				static_cast<fann_activationfunc_enum>(algo_id));
	}
	else
	{
		isolate->ThrowException(
				v8::Exception::TypeError(
						String::NewFromUtf8(isolate, "ann pointer is NULL")));
		return;
	}

}
void YNodeFANN::set_activation_function_output(
		const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = args.GetIsolate();
	YNodeFANN* obj = ObjectWrap::Unwrap<YNodeFANN>(args.Holder());

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
	int algo_id = args[0]->IsUndefined() ? 0 : args[0]->Int32Value();

	if (obj->ann != NULL)
	{
		fann_set_activation_function_output(obj->ann,
				static_cast<fann_activationfunc_enum>(algo_id));
	}
	else
	{
		isolate->ThrowException(
				v8::Exception::TypeError(
						String::NewFromUtf8(isolate, "ann pointer is NULL")));
		return;
	}

}
void YNodeFANN::set_train_error_function(
		const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = args.GetIsolate();
	YNodeFANN* obj = ObjectWrap::Unwrap<YNodeFANN>(args.Holder());

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
	int algo_id = args[0]->IsUndefined() ? 0 : args[0]->Int32Value();

	if (obj->ann != NULL)
	{
		fann_set_train_error_function(obj->ann,
				static_cast<fann_errorfunc_enum>(algo_id));
	}
	else
	{
		isolate->ThrowException(
				v8::Exception::TypeError(
						String::NewFromUtf8(isolate, "ann pointer is NULL")));
		return;
	}

}

void YNodeFANN::set_activation_function(
		const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = args.GetIsolate();
	YNodeFANN* obj = ObjectWrap::Unwrap<YNodeFANN>(args.Holder());
	// checking arguments number
	if (args.Length() < 3)
	{
		isolate->ThrowException(
				v8::Exception::TypeError(
						String::NewFromUtf8(isolate,
								"Wrong arguments number")));
		return;
	}
	// checking arguments
	int algo_id = args[0]->IsUndefined() ? 0 : args[0]->Int32Value();
	int layer = args[1]->IsUndefined() ? 0 : args[1]->Int32Value();
	int neuron = args[2]->IsUndefined() ? 0 : args[2]->Int32Value();

	if (obj->ann != NULL)
	{
		fann_set_activation_function(obj->ann,
				static_cast<fann_activationfunc_enum>(algo_id), layer, neuron);
	}
	else
	{
		isolate->ThrowException(
				v8::Exception::TypeError(
						String::NewFromUtf8(isolate, "ann pointer is NULL")));
		return;
	}

}

void YNodeFANN::set_cascade_activation_functions(
		const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = args.GetIsolate();
	YNodeFANN* obj = ObjectWrap::Unwrap<YNodeFANN>(args.Holder());
	if (args.Length() < 2)
	{
		isolate->ThrowException(
				v8::Exception::TypeError(
						String::NewFromUtf8(isolate,
								"Wrong arguments number")));
		return;
	}

	// checking arguments
	int cascade_activation_steepnesses_count =
			args[1]->IsUndefined() ? 0 : args[1]->Int32Value();

	if (cascade_activation_steepnesses_count < 0)
	{
		isolate->ThrowException(
				v8::Exception::TypeError(
						String::NewFromUtf8(isolate,
								"Wrong argument: cascade_activation_steepnesses_count")));
		return;
	}

	int *cascade_activation_functions = (int *) malloc(
			cascade_activation_steepnesses_count * sizeof(int));
	if ( NULL == cascade_activation_functions)
	{
		isolate->ThrowException(
				v8::Exception::TypeError(
						String::NewFromUtf8(isolate,
								"Allocating memory failed.")));
		return;
	}
	v8::Handle<v8::Value> theArg = args[0];
	if (theArg->IsArray())
	{
		v8::Handle<v8::Array> theArray = v8::Handle<v8::Array>::Cast(theArg);
		for (int i = 0; i < cascade_activation_steepnesses_count; i++)
		{
			v8::Handle<v8::Value> arrayItem = theArray->Get(
					v8::Int32::New(isolate, i));
			cascade_activation_functions[i] =
					arrayItem->IsUndefined() ? 0.0 : arrayItem->Int32Value();
		}
	}
	else
	{
		printf("create_sparse_array: the first argument should be an array.\n");
		free(cascade_activation_functions);
		return;
	}

	if (obj->ann != NULL)
	{
		fann_set_cascade_activation_functions(obj->ann,
				reinterpret_cast<enum fann_activationfunc_enum *>(cascade_activation_functions),
				cascade_activation_steepnesses_count);
	}
	else
	{
		isolate->ThrowException(
				v8::Exception::TypeError(
						String::NewFromUtf8(isolate, "ann pointer is NULL")));
		free(cascade_activation_functions);
		return;
	}
	free(cascade_activation_functions);
	return;
}

void YNodeFANN::get_num_input(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = args.GetIsolate();
	YNodeFANN* obj = ObjectWrap::Unwrap<YNodeFANN>(args.Holder());

	if (obj->ann != NULL)
	{
		float num_input = fann_get_num_input(obj->ann);
		args.GetReturnValue().Set(v8::Number::New(isolate, num_input));
		return;
	}
	else
	{
		isolate->ThrowException(
				v8::Exception::TypeError(
						String::NewFromUtf8(isolate, "ann pointer is NULL")));
		return;
	}
}

void YNodeFANN::get_num_output(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = args.GetIsolate();
	YNodeFANN* obj = ObjectWrap::Unwrap<YNodeFANN>(args.Holder());

	if (obj->ann != NULL)
	{
		float num_output = fann_get_num_output(obj->ann);
		args.GetReturnValue().Set(v8::Number::New(isolate, num_output));
		return;
	}
	else
	{
		isolate->ThrowException(
				v8::Exception::TypeError(
						String::NewFromUtf8(isolate, "ann pointer is NULL")));
		return;
	}
}

void YNodeFANN::get_learning_rate(
		const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = args.GetIsolate();
	YNodeFANN* obj = ObjectWrap::Unwrap<YNodeFANN>(args.Holder());

	if (obj->ann != NULL)
	{
		float learning_rate = fann_get_learning_rate(obj->ann);
		args.GetReturnValue().Set(v8::Number::New(isolate, learning_rate));
		return;
	}
	else
	{
		isolate->ThrowException(
				v8::Exception::TypeError(
						String::NewFromUtf8(isolate, "ann pointer is NULL")));
		return;
	}
}

void YNodeFANN::set_learning_rate(
		const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = args.GetIsolate();
	YNodeFANN* obj = ObjectWrap::Unwrap<YNodeFANN>(args.Holder());
	if (args.Length() < 1)
	{
		isolate->ThrowException(
				v8::Exception::TypeError(
						String::NewFromUtf8(isolate,
								"Wrong arguments number")));
		return;
	}
	// checking arguments
	float learning_rate = args[0]->IsUndefined() ? 0.0 : args[0]->NumberValue();

	if (obj->ann != NULL)
	{
		fann_set_learning_rate(obj->ann, learning_rate);
	}
	else
	{
		isolate->ThrowException(
				v8::Exception::TypeError(
						String::NewFromUtf8(isolate, "ann pointer is NULL")));
		return;
	}

}

void YNodeFANN::set_learning_momentum(
		const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = args.GetIsolate();
	YNodeFANN* obj = ObjectWrap::Unwrap<YNodeFANN>(args.Holder());
	if (args.Length() < 1)
	{
		isolate->ThrowException(
				v8::Exception::TypeError(
						String::NewFromUtf8(isolate,
								"Wrong arguments number")));
		return;
	}
	// checking arguments
	float learning_momentum =
			args[0]->IsUndefined() ? 0 : args[0]->NumberValue();

	if (obj->ann != NULL)
	{
		fann_set_learning_momentum(obj->ann, learning_momentum);
	}
	else
	{
		isolate->ThrowException(
				v8::Exception::TypeError(
						String::NewFromUtf8(isolate, "ann pointer is NULL")));
		return;
	}

}

void YNodeFANN::set_weight(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = args.GetIsolate();
	YNodeFANN* obj = ObjectWrap::Unwrap<YNodeFANN>(args.Holder());
	if (args.Length() < 3)
	{
		isolate->ThrowException(
				v8::Exception::TypeError(
						String::NewFromUtf8(isolate,
								"Wrong arguments number")));
		return;
	}
	// checking arguments
	int from_neuron = args[0]->IsUndefined() ? 0 : args[0]->Int32Value();
	int to_neuron = args[1]->IsUndefined() ? 0 : args[1]->Int32Value();
	float weight = args[2]->IsUndefined() ? 0 : args[2]->NumberValue();

	if (obj->ann != NULL)
	{
		fann_set_weight(obj->ann, from_neuron, to_neuron, weight);
	}
	else
	{
		isolate->ThrowException(
				v8::Exception::TypeError(
						String::NewFromUtf8(isolate, "ann pointer is NULL")));
		return;
	}
}

void YNodeFANN::set_cascade_activation_steepnesses(
		const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = args.GetIsolate();
	YNodeFANN* obj = ObjectWrap::Unwrap<YNodeFANN>(args.Holder());
	if (args.Length() < 2)
	{
		isolate->ThrowException(
				v8::Exception::TypeError(
						String::NewFromUtf8(isolate,
								"Wrong arguments number")));
		return;
	}

	// checking arguments
	int cascade_activation_steepnesses_count =
			args[1]->IsUndefined() ? 0 : args[1]->Int32Value();

	if (cascade_activation_steepnesses_count < 0)
	{
		isolate->ThrowException(
				v8::Exception::TypeError(
						String::NewFromUtf8(isolate,
								"Wrong argument: cascade_activation_steepnesses_count")));
		return;
	}

	float *cascade_activation_steepnesses = (float *) malloc(
			cascade_activation_steepnesses_count * sizeof(float));
	if ( NULL == cascade_activation_steepnesses)
	{
		isolate->ThrowException(
				v8::Exception::TypeError(
						String::NewFromUtf8(isolate,
								"Allocating memory failed.")));
		return;
	}
	v8::Handle<v8::Value> theArg = args[0];
	if (theArg->IsArray())
	{
		v8::Handle<v8::Array> theArray = v8::Handle<v8::Array>::Cast(theArg);
		for (int i = 0; i < cascade_activation_steepnesses_count; i++)
		{
			v8::Handle<v8::Value> arrayItem = theArray->Get(
					v8::Int32::New(isolate, i));
			cascade_activation_steepnesses[i] =
					arrayItem->IsUndefined() ? 0.0 : arrayItem->NumberValue();
		}
	}
	else
	{
		printf("create_sparse_array: the first argument should be an array.\n");
		free(cascade_activation_steepnesses);
		return;
	}

	if (obj->ann != NULL)
	{
		fann_set_cascade_activation_steepnesses(obj->ann,
				cascade_activation_steepnesses,
				cascade_activation_steepnesses_count);
	}
	else
	{
		isolate->ThrowException(
				v8::Exception::TypeError(
						String::NewFromUtf8(isolate, "ann pointer is NULL")));
		free(cascade_activation_steepnesses);
		return;
	}
	free(cascade_activation_steepnesses);
	return;
}

void YNodeFANN::set_activation_steepness(
		const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = args.GetIsolate();
	YNodeFANN* obj = ObjectWrap::Unwrap<YNodeFANN>(args.Holder());
	if (args.Length() < 3)
	{
		isolate->ThrowException(
				v8::Exception::TypeError(
						String::NewFromUtf8(isolate,
								"Wrong arguments number")));
		return;
	}
	// checking arguments
	float steepness = args[0]->IsUndefined() ? 0 : args[0]->NumberValue();
	int layer = args[1]->IsUndefined() ? 0 : args[1]->Int32Value();
	int neuron = args[2]->IsUndefined() ? 0 : args[2]->Int32Value();

	if (obj->ann != NULL)
	{
		fann_set_activation_steepness(obj->ann, steepness, layer, neuron);
	}
}

void YNodeFANN::set_activation_steepness_layer(
		const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = args.GetIsolate();
	YNodeFANN* obj = ObjectWrap::Unwrap<YNodeFANN>(args.Holder());
	if (args.Length() < 2)
	{
		isolate->ThrowException(
				v8::Exception::TypeError(
						String::NewFromUtf8(isolate,
								"Wrong arguments number")));
		return;
	}
	// checking arguments
	float steepness = args[0]->IsUndefined() ? 0 : args[0]->NumberValue();
	int layer = args[1]->IsUndefined() ? 0 : args[1]->Int32Value();

	if (obj->ann != NULL)
	{
		fann_set_activation_steepness_layer(obj->ann, steepness, layer);
	}
}

void YNodeFANN::set_activation_steepness_hidden(
		const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = args.GetIsolate();
	YNodeFANN* obj = ObjectWrap::Unwrap<YNodeFANN>(args.Holder());
	if (args.Length() < 1)
	{
		isolate->ThrowException(
				v8::Exception::TypeError(
						String::NewFromUtf8(isolate,
								"Wrong arguments number")));
		return;
	}
	// checking arguments
	float steepness = args[0]->IsUndefined() ? 0 : args[0]->NumberValue();
	//int layer = args[1]->IsUndefined() ? 0 : args[1]->Int32Value();

	if (obj->ann != NULL)
	{
		fann_set_activation_steepness_hidden(obj->ann, steepness);
	}
}

void YNodeFANN::set_activation_steepness_output(
		const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = args.GetIsolate();
	YNodeFANN* obj = ObjectWrap::Unwrap<YNodeFANN>(args.Holder());
	if (args.Length() < 1)
	{
		isolate->ThrowException(
				v8::Exception::TypeError(
						String::NewFromUtf8(isolate,
								"Wrong arguments number")));
		return;
	}
	// checking arguments
	float steepness = args[0]->IsUndefined() ? 0 : args[0]->NumberValue();
	//int layer = args[1]->IsUndefined() ? 0 : args[1]->Int32Value();

	if (obj->ann != NULL)
	{
		fann_set_activation_steepness_output(obj->ann, steepness);
	}
}

void YNodeFANN::create_sparse_array(
		const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = args.GetIsolate();
	YNodeFANN* obj = ObjectWrap::Unwrap<YNodeFANN>(args.Holder());

	// checking arguments number
	if (args.Length() < 3)
	{
		isolate->ThrowException(
				v8::Exception::TypeError(
						String::NewFromUtf8(isolate,
								"Wrong arguments number")));
		return;
	}
	// checking arguments
	for (int i = 0; i < 3; i++)
	{
		if (args[i]->IsUndefined())
		{
			printf("create_sparse_array: argument %d is an undefined value.\n",
					i);
			isolate->ThrowException(
					v8::Exception::TypeError(
							String::NewFromUtf8(isolate,
									"create_sparse_array: argument %d is an undefined value.")));
			return;
		}
	}

	float connection_rate = args[0]->IsUndefined() ? 0 : args[0]->NumberValue();

	unsigned int len = 0;
	if (args[1]->IsInt32())
	{
		len = (unsigned int) (args[1]->Int32Value());
	}
	else
	{
		printf(
				"create_sparse_array: the second argument should be an integer.\n");
		return;
	}

	unsigned int *layers = (unsigned int*) malloc((len) * sizeof(unsigned int));
	if ( NULL == layers)
	{
		printf("create_sparse_array: allocating memory fail.\n");
		return;
	}

	v8::Handle<v8::Value> theArg = args[2];

	if (theArg->IsArray())
	{
		v8::Handle<v8::Array> theArray = v8::Handle<v8::Array>::Cast(theArg);
		for (int i = 0; i < len; i++)
		{
			v8::Handle<v8::Value> arrayItem = theArray->Get(
					v8::Int32::New(isolate, i));
			layers[i] = (unsigned int) (arrayItem->Int32Value());
		}
		if (obj->ann != NULL)
		{
			fann_destroy(obj->ann);
			obj->ann = NULL;
		}

		obj->ann = fann_create_sparse_array(connection_rate, len, layers);
	}
	else
	{
		printf("create_sparse_array: the third argument should be an array.\n");
		return;
	}

	if (obj->ann == NULL)
	{
		printf("ERROR: creating ann pointer failed.\n");
	}

	free(layers);
	layers = NULL;
	return;
}

void YNodeFANN::create_shortcut_array(
		const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = args.GetIsolate();
	YNodeFANN* obj = ObjectWrap::Unwrap<YNodeFANN>(args.Holder());

	int len = args[0]->IsUndefined() ? 0 : args[0]->Int32Value();

	unsigned int *layers = (unsigned int*) malloc((len) * sizeof(unsigned int));
	if ( NULL == layers)
	{
		printf("create_shortcut_array: allocating memory fail.\n");
		return;
	}
	v8::Handle<v8::Value> theArg = args[1];

	if (theArg->IsArray())
	{
		v8::Handle<v8::Array> theArray = v8::Handle<v8::Array>::Cast(theArg);
		for (int i = 0; i < len; i++)
		{
			v8::Handle<v8::Value> arrayItem = theArray->Get(
					v8::Int32::New(isolate, i));
			layers[i] = arrayItem->Int32Value();
		}

		if (obj->ann != NULL)
		{
			fann_destroy(obj->ann);
			obj->ann = NULL;
		}
		obj->ann = fann_create_shortcut_array(len, layers);
	}
	if (obj->ann == NULL)
	{
		free(layers);
		layers = NULL;
		isolate->ThrowException(
				v8::Exception::TypeError(
						String::NewFromUtf8(isolate, "ann pointer is NULL")));

		return;
	}

	free(layers);
	layers = NULL;
	return;
}

// fann_create_standard_array
void YNodeFANN::create_standard_array(
		const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = args.GetIsolate();
	YNodeFANN* obj = ObjectWrap::Unwrap<YNodeFANN>(args.Holder());

	if (args.Length() < 2)
	{
		isolate->ThrowException(
				v8::Exception::TypeError(
						String::NewFromUtf8(isolate,
								"Wrong arguments number")));
		return;
	}

	unsigned int len = 0;
	if (args[0]->IsInt32())
	{
		len = (unsigned int) (args[0]->Int32Value());
	}
	else
	{
		printf(
				"create_standard_array: the first argument should be an integer.\n");
		return;
	}

	unsigned int *layers = (unsigned int*) malloc((len) * sizeof(unsigned int));
	if ( NULL == layers)
	{
		printf("create_standard_array: allocating memory fail.\n");
		return;
	}

	v8::Handle<v8::Value> theArg = args[1];

	if (theArg->IsArray())
	{
		v8::Handle<v8::Array> theArray = v8::Handle<v8::Array>::Cast(theArg);
		for (int i = 0; i < len; i++)
		{
			v8::Handle<v8::Value> arrayItem = theArray->Get(
					v8::Int32::New(isolate, i));
			layers[i] = (unsigned int) (arrayItem->Int32Value());
		}

		if (obj->ann != NULL)
		{
			fann_destroy(obj->ann);
			obj->ann = NULL;
		}
		obj->ann = fann_create_standard_array(len, layers);
	}
	else
	{
		printf(
				"create_standard_array: the second argument should be an array.\n");
		return;
	}

	if (obj->ann == NULL)
	{
		printf("ERROR: creating ann pointer failed.\n");
	}

	free(layers);
	layers = NULL;
	return;

}

void YNodeFANN::create_from_file(
		const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = args.GetIsolate();
	YNodeFANN* obj = ObjectWrap::Unwrap<YNodeFANN>(args.Holder());

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
		// destroy();
		if (obj->ann != NULL)
		{
			fann_destroy(obj->ann);
			obj->ann = NULL;
		}

		obj->ann = fann_create_from_file(name);
		if (!(obj->ann))
		{
			printf("Error creating ann --- ABORTING.\n");
			return;
		}
	}
}

void YNodeFANN::destroy(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = args.GetIsolate();
	YNodeFANN* obj = ObjectWrap::Unwrap<YNodeFANN>(args.Holder());

	if (obj->ann != NULL)
	{
//        user_context *user_data = static_cast<user_context *>(fann_get_user_data(obj->ann));
//        if (user_data != NULL)
//            delete user_data;

		fann_destroy(obj->ann);
		obj->ann = NULL;
	}

	return;
}

void YNodeFANN::get_MSE(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = args.GetIsolate();
	YNodeFANN* obj = ObjectWrap::Unwrap<YNodeFANN>(args.Holder());

	float mse = 0.0;
	if (obj->ann != NULL)
	{
		mse = fann_get_MSE(obj->ann);
	}
	else
	{
		isolate->ThrowException(
				v8::Exception::TypeError(
						String::NewFromUtf8(isolate, "ann pointer is NULL.")));
	}
	args.GetReturnValue().Set(v8::Number::New(isolate, mse));
	return;
}

void YNodeFANN::train_on_data(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = args.GetIsolate();
	YNodeFANN* obj = ObjectWrap::Unwrap<YNodeFANN>(args.Holder());
	// checking arguments number
	if (args.Length() < 4)
	{
		isolate->ThrowException(
				v8::Exception::TypeError(
						String::NewFromUtf8(isolate,
								"Wrong arguments number")));
		return;
	}
	// checking arguments
	for (int i = 0; i < 4; i++)
	{
		if (args[i]->IsUndefined())
		{
			printf("create_sparse_array: argument %d is an undefined value.\n",
					i);
			isolate->ThrowException(
					v8::Exception::TypeError(
							String::NewFromUtf8(isolate,
									"create_sparse_array: one argument is an undefined value.")));
			return;
		}
	}

	YNodeFANNTrainData* trainData =
			node::ObjectWrap::Unwrap<YNodeFANNTrainData>(args[0]->ToObject());

	int max_epochs = args[1]->Int32Value();
	unsigned int epochs_between_reports = args[2]->Int32Value();
	float desired_error = args[3]->NumberValue();

	if ((obj->ann != NULL) && (trainData->train_data != NULL))
	{
		fann_train_on_data(obj->ann, trainData->train_data, max_epochs,
				epochs_between_reports, desired_error);
	}

}

void YNodeFANN::train_on_file(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = args.GetIsolate();
	YNodeFANN* obj = ObjectWrap::Unwrap<YNodeFANN>(args.Holder());

	// checking arguments number
	if (args.Length() < 3)
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
		int max_epochs = args[1]->Int32Value();
		unsigned int epochs_between_reports = args[2]->Int32Value();
		float desired_error = args[3]->NumberValue();

		if (obj->ann != NULL)
		{
			fann_train_on_file(obj->ann, name, max_epochs,
					epochs_between_reports, desired_error);
		}
	}

}

void YNodeFANN::run(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = args.GetIsolate();
	YNodeFANN* obj = ObjectWrap::Unwrap<YNodeFANN>(args.Holder());

	if (args[0]->IsUndefined())
	{
		//std::cerr << "In run(): parameters undefined." << std::endl;
		return;
	}
	v8::Handle<v8::Value> theArg = args[0];

	if (theArg->IsArray())
	{
		v8::Handle<v8::Array> theArray = v8::Handle<v8::Array>::Cast(theArg);

		int length = theArray->Length();
		float* input = (float*) malloc(length * sizeof(float));

		for (int i = 0; i < length; i++)
		{
			v8::Handle<v8::Value> arrayItem = theArray->Get(
					v8::Int32::New(isolate, i));
			input[i] = arrayItem->NumberValue();
		}

		if (obj->ann == NULL)
		{
			printf("ERROR: ann pointer is NULL.\n");
			free(input);
			input = NULL;
			return;
		}

		float *result = fann_run(obj->ann, input);

		free(input);
		input = NULL;

		if ( NULL != result)
		{
			int output_number = obj->ann->num_output;

			//printf( "result array length: %d \n", output_number );

			v8::Handle<v8::Array> resultArray = v8::Array::New(isolate);
			for (int i = 0; i < output_number; i++)
			{
				resultArray->Set(v8::Integer::New(isolate, i),
						v8::Number::New(isolate, result[i]));
			}
			args.GetReturnValue().Set(resultArray);
		}
		else
		{
			printf("result run() is NULL.\n");
		}
	}
	return;
}

void YNodeFANN::test_data(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = args.GetIsolate();
	YNodeFANN* obj = ObjectWrap::Unwrap<YNodeFANN>(args.Holder());
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
	for (int i = 0; i < 1; i++)
	{
		if (args[i]->IsUndefined())
		{
			printf("create_sparse_array: argument %d is an undefined value.\n",
					i);
			isolate->ThrowException(
					v8::Exception::TypeError(
							String::NewFromUtf8(isolate,
									"create_sparse_array: one argument is an undefined value.")));
			return;
		}
	}

	YNodeFANNTrainData* trainData =
			node::ObjectWrap::Unwrap<YNodeFANNTrainData>(args[0]->ToObject());

	if ((obj->ann != NULL) && (trainData->train_data != NULL))
	{
		fann_test_data(obj->ann, trainData->train_data);
	}
}

void YNodeFANN::test(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = args.GetIsolate();
	YNodeFANN* obj = ObjectWrap::Unwrap<YNodeFANN>(args.Holder());
	// checking arguments number
	if (obj->ann == NULL)
	{
		isolate->ThrowException(
				v8::Exception::TypeError(
						String::NewFromUtf8(isolate, "ann pointer is NULL")));
		return;
	}

	if (args.Length() < 2)
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

	if (args[1]->IsUndefined())
	{
		isolate->ThrowException(
				v8::Exception::TypeError(
						String::NewFromUtf8(isolate,
								"one argument is an undefined value.")));
		return;
	}

	v8::Handle<v8::Array> inputArray;
	v8::Handle<v8::Array> outputArray;

	if (args[0]->IsArray())
	{
		inputArray = v8::Handle<v8::Array>::Cast(args[0]);
	}
	else
	{
		isolate->ThrowException(
				v8::Exception::TypeError(
						String::NewFromUtf8(isolate,
								"argument is NOT an array.")));
		return;
	}
	if (args[1]->IsArray())
	{
		outputArray = v8::Handle<v8::Array>::Cast(args[1]);
	}
	else
	{
		isolate->ThrowException(
				v8::Exception::TypeError(
						String::NewFromUtf8(isolate,
								"argument is NOT an array.")));
		return;
	}

	int inputlength = inputArray->Length();

	float* input = (float*) malloc(inputlength * sizeof(float));
	if ( NULL == input)
	{
		isolate->ThrowException(
				v8::Exception::TypeError(
						String::NewFromUtf8(isolate,
								"allocating memory failed.")));
		return;
	}
	for (int i = 0; i < inputlength; i++)
	{
		v8::Handle<v8::Value> arrayItem = inputArray->Get(
				v8::Int32::New(isolate, i));
		input[i] = arrayItem->NumberValue();
	}

	int outputlength = outputArray->Length();
	float* output = (float*) malloc(outputlength * sizeof(float));
	if ( NULL == output)
	{
		free(input);
		input = NULL;
		isolate->ThrowException(
				v8::Exception::TypeError(
						String::NewFromUtf8(isolate,
								"allocating memory failed.")));
		return;
	}
	for (int i = 0; i < outputlength; i++)
	{
		v8::Handle<v8::Value> arrayItem = outputArray->Get(
				v8::Int32::New(isolate, i));
		output[i] = arrayItem->NumberValue();
	}

	float *result = fann_test(obj->ann, input, output);

	free(output);
	output = NULL;
	free(input);
	input = NULL;

	if ( NULL != result)
	{
		v8::Handle<v8::Array> resultArray = v8::Array::New(isolate);
		for (int i = 0; i < outputlength; i++)
		{
			resultArray->Set(v8::Integer::New(isolate, i),
					v8::Number::New(isolate, result[i]));
			// DEBUG
			//printf( "result[%d] = %f \n", i, result[i] );
			// DEBUG
		}
		args.GetReturnValue().Set(resultArray);
		return;
	}
	else
	{
		isolate->ThrowException(
				v8::Exception::TypeError(
						String::NewFromUtf8(isolate,
								"result of test() is NULL.")));
	}

	return;
}

void YNodeFANN::save(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = args.GetIsolate();
	YNodeFANN* obj = ObjectWrap::Unwrap<YNodeFANN>(args.Holder());

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

	if (obj->ann == NULL)
	{
		printf("save ann failed, ann pointer is NULL.\n");
		return;
	}

	if (args[0]->IsString())
	{
		char *configuration_file;
		v8::String::Utf8Value str(args[0]->ToString());
		configuration_file = *str;

		if (fann_save(obj->ann, configuration_file) == -1)
		{
			printf("save ann failed.\n");
			return;
		}
	}
	else
	{
		printf("save ann failed, the argument is NOT a string.\n");
		return;
	}
}

void YNodeFANN::print_connections(
		const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = args.GetIsolate();
	YNodeFANN* obj = ObjectWrap::Unwrap<YNodeFANN>(args.Holder());

	if (obj->ann == NULL)
	{
		printf("Print ann connections failed, ann pointer is NULL.\n");
		return;
	}

	fann_print_connections(obj->ann);
	return;
}

