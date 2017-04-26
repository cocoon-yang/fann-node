/*
 * ynodefann.h
 *
 *  Created on: April, 2017
 *      Author: Chunfeng Yang
 */

#ifndef NODE_INC_YNODEFANN_H_
#define NODE_INC_YNODEFANN_H_

#include <node.h>
#include <node_object_wrap.h>
#include "fann.h"

class YNodeFANN: public node::ObjectWrap {
public:
	static void Init(v8::Local<v8::Object> exports);

private:
	explicit YNodeFANN();
	~YNodeFANN();

	static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
	static v8::Persistent<v8::Function> constructor;

	static void create_standard_array(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void create_sparse_array(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void create_shortcut_array(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void create_from_file(const v8::FunctionCallbackInfo<v8::Value>& args);

	static void destroy(const v8::FunctionCallbackInfo<v8::Value>& args);

	static void set_training_algorithm(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void set_activation_function_hidden(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void set_activation_function_output(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void set_train_error_function(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void set_activation_function(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void set_cascade_activation_functions(const v8::FunctionCallbackInfo<v8::Value>& args);

	static void set_cascade_activation_steepnesses(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void set_weight(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void set_learning_momentum(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void set_activation_steepness(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void set_activation_steepness_layer(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void set_activation_steepness_hidden(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void set_activation_steepness_output(const v8::FunctionCallbackInfo<v8::Value>& args);

	static void get_num_input(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void get_num_output(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void get_learning_rate(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void set_learning_rate(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void get_MSE(const v8::FunctionCallbackInfo<v8::Value>& args);

	static void train_on_data(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void train_on_file(const v8::FunctionCallbackInfo<v8::Value>& args);

	static void test(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void test_data(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void run(const v8::FunctionCallbackInfo<v8::Value>& args);

	static void save(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void print_connections(const v8::FunctionCallbackInfo<v8::Value>& args);

private:
	struct fann *ann;
};
#endif /* NODE_INC_YNODEFANN_H_ */
