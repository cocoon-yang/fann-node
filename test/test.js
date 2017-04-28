
/******************
 *
 *  constructing neural network model from train data set 
 *
 ******************/
//
// module
var yfann = require('./build/release/fann')

var fann = new yfann.YNodeFANN( );
var test_data = new yfann.YNodeFANNTrainData( );
var train_data = new yfann.YNodeFANNTrainData( );


/*******************
test_data.read_train_from_file('./abelone.train');
train_data.read_train_from_file('./abelone.test');

var input = train_data.num_input_train_data()
var output = train_data.num_output_train_data()


console.log( ' input: ', input );
console.log( 'output: ', output );

fann.create_standard_array( parseInt(4),  Array( input, 100, 100, output ) );

fann.set_training_algorithm( 2 );
fann.set_learning_momentum(0.2)



fann.train_on_data( train_data, 2000, 500, 0.001 );


 
var result = fann.run( [0,0,0.353920,0.148646,0.115024,0.040701,0.111131,0.045833,0.022474,0.035392 ] );
console.log( 'result:', result  );
***********************/ 


function cascade()
{
	test_data.read_train_from_file('./parity8.train');
	train_data.read_train_from_file('./parity8.test');

	var input = train_data.num_input_train_data()
	var output = train_data.num_output_train_data()

	console.log( ' input: ', input );
	console.log( 'output: ', output );

	train_data.scale_train_data( -1, 1);
	test_data.scale_train_data( -1, 1);
	
	
	fann.create_shortcut(2, input, output );
	
	fann.set_training_algorithm( 2 );  // FANN_TRAIN_RPROP;
	fann.set_activation_function_hidden( 5 );  // ann, FANN_SIGMOID_SYMMETRIC
	fann.set_activation_function_output( 0 );  // ann, FANN_LINEAR
	fann.set_train_error_function( 0 );	 // ann, FANN_ERRORFUNC_LINEAR
	
	
	var testdata = []
	var result = fann.run( testdata );

	console.log( 'result:', result[0]  );
	
}  
 
 
 
 
 function mushroom()
 {
 	var num_layers = 3;
 	var num_neurons_hidden = 32;
 	var desired_error =  0.0001;
 	var max_epochs = 300;
 	var epochs_between_reports = 10;
 	
 	console.log("Creating network.\n");
 	
 	train_data.read_train_from_file('../datasets/mushroom.train');
 
 	var input = train_data.num_input_train_data()
	var output = train_data.num_output_train_data()

	console.log( ' input: ', input );
	console.log( 'output: ', output );
 
 	fann.create_standard_array(num_layers, [input, num_neurons_hidden,  output]);
	fann.set_activation_function_hidden(  6 ); // FANN_SIGMOID_SYMMETRIC_STEPWISE)
	fann.set_activation_function_output( 4 );	// FANN_SIGMOID_STEPWISE	
	
	fann.train_on_data( train_data, max_epochs, epochs_between_reports, desired_error);	
	
	console.log("Testing network.\n");	  
	
	var testdata = [0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,1,0,1,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,1,0,0,0,1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,1]
	var result = fann.run( testdata );

	console.log( 'result:', result  );
		
 }
 
 
 
 function pumadyn()
 {
  	var num_layers = 3;
 	var num_neurons_hidden = 32;
 	var desired_error =  0.0001;
 	var max_epochs = 300;
 	var epochs_between_reports = 10;
 	
 	console.log("Creating network.\n");
 	
 	test_data.read_train_from_file('../datasets/pumadyn-32fm.test');
    train_data.read_train_from_file('../datasets/pumadyn-32fm.train');
    
    
 	var input = train_data.num_input_train_data()
	var output = train_data.num_output_train_data()

	console.log( ' input: ', input );
	console.log( 'output: ', output );
 
 	fann.create_standard_array(num_layers, [input, num_neurons_hidden,  output]);
	fann.set_activation_function_hidden(  6 ); // FANN_SIGMOID_SYMMETRIC_STEPWISE)
	fann.set_activation_function_output( 4 );	// FANN_SIGMOID_STEPWISE	
	
 	fann.train_on_data( train_data, max_epochs, epochs_between_reports, desired_error);	
	
	console.log("Testing network.\n");	 
 	var testdata = [0.485265,0.496498,0.503016,0.490695,0.485165,0.489131,0.505908,0.506213,0.502395,0.505477,0.499453,0.504030,0.830962,0.629794,0.883773,0.588814,0.400239,0.523277,0.515112,0.520103,0.518687,0.524354,0.512448,0.517644,0.515489,0.515527,0.512288,0.511747,0.514934,0.517329,0.513065,0.517594]
 	
 	// var result = fann.test( testdata, Array([0.416431]) );
 	var result = fann.run( testdata  );
 	
	console.log( 'result:', result  );
	
	
    fann.test_data( test_data);
 
}
 
pumadyn();
mushroom();
 
fann.destroy();
test_data.destroy();
train_data.destroy();



















