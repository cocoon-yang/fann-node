/*
 * ynodefanntraindata.h
 *
 *  Created on: April, 2017
 *      Author: Chunfeng Yang
 */

#ifndef NODE_INC_YNODEFANNTRAINDATA_H_
#define NODE_INC_YNODEFANNTRAINDATA_H_

#include <node.h>
#include <node_object_wrap.h>
#include "fann.h"

class YNodeFANNTrainData: public node::ObjectWrap
{
public:
	static void Init(v8::Local<v8::Object> exports);

private:
	explicit YNodeFANNTrainData();
	virtual ~YNodeFANNTrainData();

	static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
	static v8::Persistent<v8::Function> constructor;

	static void read_train_from_file(const v8::FunctionCallbackInfo<v8::Value>& args);

	static void length_train_data(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void num_input_train_data(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void num_output_train_data(const v8::FunctionCallbackInfo<v8::Value>& args);

	static void scale_input_train_data( const v8::FunctionCallbackInfo<v8::Value>& args);
	static void scale_output_train_data( const v8::FunctionCallbackInfo<v8::Value>& args);
	static void scale_train_data( const v8::FunctionCallbackInfo<v8::Value>& args);

	static void destroy(const v8::FunctionCallbackInfo<v8::Value>& args);

	static void save(const v8::FunctionCallbackInfo<v8::Value>& args);
private:
	/* Pointer to the encapsulated training data */
	struct fann_train_data* train_data;

	friend class YNodeFANN;
};

#endif /* NODE_INC_YNODEFANNTRAINDATA_H_ */
