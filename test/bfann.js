/******************
 *
 *  constructing neural network model from train data set 
 *
 ******************/
// module
var yfann = require('./build/release/fann')
//activation_function_enum {
        LINEAR = FANN_LINEAR = 0;
        THRESHOLD=1
        THRESHOLD_SYMMETRIC = 2
        SIGMOID = 3
        SIGMOID_STEPWISE = 4
        SIGMOID_SYMMETRIC = 5
        SIGMOID_SYMMETRIC_STEPWISE = 6
        GAUSSIAN = 7
        GAUSSIAN_SYMMETRIC =8
        GAUSSIAN_STEPWISE = 9
        ELLIOT = 10
        ELLIOT_SYMMETRIC = 11
        LINEAR_PIECE =12
        LINEAR_PIECE_SYMMETRIC = 13
	    SIN_SYMMETRIC = 14
	    COS_SYMMETRIC = 15


var training_algorithm_list = [];

training_algorithm_list.push( "TRAIN_INCREMENTAL" ); // = FANN_TRAIN_INCREMENTAL,
training_algorithm_list.push( "TRAIN_BATCH" ); 
training_algorithm_list.push( "TRAIN_RPROP" ); 
training_algorithm_list.push( "TRAIN_QUICKPROP" ); 
training_algorithm_list.push( "TRAIN_SARPROP" ); 



var activation_function_list = [];
activation_function_list.push( 'LINEAR' ); // = FANN_LINEAR,
activation_function_list.push( 'THRESHOLD' );
activation_function_list.push( 'THRESHOLD_SYMMETRIC' );
activation_function_list.push( 'SIGMOID' );
activation_function_list.push( 'SIGMOID_STEPWISE' );
activation_function_list.push( 'SIGMOID_SYMMETRIC' );
activation_function_list.push( 'SIGMOID_SYMMETRIC_STEPWISE' );
activation_function_list.push( 'GAUSSIAN' );
activation_function_list.push( 'GAUSSIAN_SYMMETRIC' );
activation_function_list.push( 'GAUSSIAN_STEPWISE' );
activation_function_list.push( 'ELLIOT' );
activation_function_list.push( 'ELLIOT_SYMMETRIC' );
activation_function_list.push( 'LINEAR_PIECE' );
activation_function_list.push( 'LINEAR_PIECE_SYMMETRIC' );
activation_function_list.push( 'SIN_SYMMETRIC' );
activation_function_list.push( 'COS_SYMMETRIC' );

//
// variables
//
var fann = new yfann.YNodeFANN( );
var test_data = new yfann.YNodeFANNTrainData( );
var train_data = new yfann.YNodeFANNTrainData( );

var trainfilepath = './bmw.train'; 

var num_layers = 4;
var num_neurons_hidden = 400;
var desired_error =  0.01;

var layers = [];

//
//
//
train_data.read_train_from_file( trainfilepath );
// train_data.scale_train_data( -1, 1);


var input = train_data.num_input_train_data()
var output = train_data.num_output_train_data()

console.log( ' input: ', input );
console.log( 'output: ', output );

// construct layers array 
layers.push( input ); 
for( var i = 0; i < num_layers - 2; i++ )
{
    layers.push( num_neurons_hidden );
}
layers.push( output );







// fann.train_on_data( train_data, 200, 100, 0.1 );


 
var testdata = [0.2037,0.1764,0.1840,0.2379,0.2242,0.1721,0.1875,0.1786,0.1786,0.2255,-0.0556,-0.0556,0.0455,0.0413,-0.0632,-0.0531,0.0459,0.0484,-0.0618,-0.0587,-0.0556,-0.0632,-0.0556,-0.0587,-0.0537,-0.0511,-0.0506,-0.0587,-0.0556,-0.0556,-0.0531,-0.0562,-0.0537,-0.0376,-0.2122,-0.2143,0.0215,0.0240,-0.0587,-0.0556,0.1178,-0.0587,-0.0556,0.0238,0.0266,-0.2143,0.0816,0.0816,-0.0556,-0.1329,0.1154,0.0051,0.0000,0.0288,0.0314,0.0238,0.0217,0.0263,0.0098,-0.0556,-0.0480,0.0102,0.0025,-0.1289,-0.1226,-0.1250,-0.1178,0.1178,-0.0650,-0.0531,0.1178,0.1139,0.1187,0.1154,0.1154,0.1187,-0.1289,0.3958,0.3958,0.2829,0.3196,0.1109,0.0215,-0.1250,0.0238,0.1552,-0.2122,-0.2122,0.0192,0.0238,0.1202,0.1178,0.1154,0.1250,0.1151,0.1226,0.0288,0.0238,0.1154,0.1163,0.1163,0.1094,-0.1242,-0.1289,0.0330,0.2222,0.2263,0.1163,0.1202,0.1124,0.1078,-0.1289,-0.1178,0.1154,0.1187,0.0263,0.0240,0.2407,0.2214,0.0238,0.0240,0.0192,0.0192,0.0238,0.0263,0.0263,-0.0562,0.0505,0.0288,0.0314,-0.0556,-0.1250,-0.1154,-0.1250,0.0263,0.0288,0.0238,0.0263,-0.1250,-0.1250,0.0215,0.0215,-0.1226,-0.1250,-0.1250,-0.0263,0.1178,-0.1369,-0.1429,-0.1289,-0.1289,-0.1250,-0.1410,-0.2122,-0.1078,-0.1306,0.1157,0.1178,0.2187,0.2207,0.1139,0.1178,0.1796,0.1743,-0.1250,-0.1289,0.0169,0.0215,-0.1250,-0.1289,-0.1250,-0.1289,0.1178,0.1154,-0.1250,-0.1289,0.0434,-0.1250,-0.1250,-0.1289,-0.1242,-0.1226,-0.1226,-0.1250,-0.1289,-0.1329,0.1178,0.1154,-0.0556,-0.0531,-0.1266,-0.1329,-0.1250,0.0263,-0.1203,-0.1250,-0.2132,-0.2194,0.0215,0.0238,-0.2143,-0.2143,-0.3333,-0.3319,-0.2122,-0.2122,-0.1329,-0.1250,-0.1178,-0.1203,-0.2143,-0.2143,-0.2143,-0.2143,-0.2143,-0.2143,0.0833,0.0833,0.1250,0.1178,0.0459,0.0434,0.0455,0.0479,0.0156,0.0000,-0.2101,-0.2143,0.0833,0.0882,-0.1250,-0.1226,-0.1250,-0.1289,-0.2143,-0.2194,-0.1250,-0.1250,-0.2143,-0.2122,-0.1178,-0.1226,-0.1226,-0.1226,0.1154,0.1139,-0.1250,-0.1242,-0.1387,-0.1250,-0.1250,-0.1250,0.1235,0.1139,-0.1250,-0.1329,-0.0531,-0.0789,-0.2194,-0.2246,-0.2194,-0.2122,-0.1289,-0.1250,-0.2299,-0.2143,-0.1250,-0.1226,-0.2874,-0.2734,-0.1289,-0.1306,-0.2143,-0.2122,-0.0531,-0.0714,-0.3547,-0.3333,0.1139,0.1163,-0.2194,-0.2143,-0.2194,-0.2101,-0.2122,-0.2194,-0.2194,-0.2674,-0.0531,-0.0593,-0.0650,-0.1226,-0.0556,-0.1329,-0.1242,-0.2674,-0.2674,-0.2656,-0.2692,0.0263,0.0288,0.0238,-0.1250,-0.1250,0.0215,0.0215,-0.2143,-0.2246,0.0833,0.0833,0.1154,0.1078,-0.1250,-0.1452,-0.1250,-0.1226,-0.1289,-0.3319,-0.1329,-0.1250,-0.1078,-0.1289,-0.1250,-0.1329,0.0215,0.0291,-0.1250,-0.1226,0.2435,0.2388,0.0238,0.0215,-0.1250,-0.1250,-0.2194,-0.2143,0.1190,0.2856,0.0215,0.0266,0.1154,0.2764,0.1154,0.1124,-0.0531,-0.0556,-0.1226,-0.1369,0.0215,0.0366,0.0238,0.0263,0.0288,0.0238,0.2817,0.3073,0.1178,0.1154,-0.2259,-0.2122,0.1139]


var desiredResult =  [ -0.4474 ]
/**********
console.log( 'length:', testdata.length   );
var result = fann.run( testdata );
console.log( 'result:', result   );
fann.save('./bmw.net');
*******/

function act_function () 
{

    for( var train_algo = 0; train_algo < 5; train_algo++ )
    {
      for( var i = 2; i < 16; i++ )
      {

      for( var j = 2; j < 16; j++ )
      {
          fann.create_standard_array( parseInt( num_layers ), layers  );


          fann.set_training_algorithm( train_algo );
          fann.set_learning_momentum(0.1)

          fann.set_activation_function_hidden( i );
          fann.set_activation_function_output( j );	 
	
          fann.set_activation_steepness_hidden( 0.1 );
          fann.set_activation_steepness_output( 0.2 );


          fann.train_on_data( train_data, 100, 50, 0.01 );
          var MSE = fann.get_MSE();
          var result = fann.run( testdata );

         console.log( Date() );
         console.log( 'training algorithm function : ', training_algorithm_list[train_algo] , '  ', train_algo)
         console.log( ' hidden activation_function : ', activation_function_list[i] , '  ', i )
         console.log( ' output activation_function : ', activation_function_list[j] , '  ', j )
         console.log( '                 num_layers = ', num_layers) ;
         console.log( '         num_neurons_hidden = ', num_neurons_hidden );
         console.log( '              desired_error = ', desired_error );
         console.log( '                        MSE : ', MSE );
         console.log( '              desiredResult : ', desiredResult   );
         console.log( '                     result : ', result   );
           if( parseFloat(MSE) < 0.02 )
           {
                var error = parseFloat( result[0] ) - parseFloat( desiredResult[0] );
                if( Math.abs( error ) < 0.07 ) 
                {
                       console.log( '  ----  save ann model  ----  ' );
                       fann.save('./bmw_'+ activation_function_list[i] + '.net');
                 }
            }
           console.log( );
           fann.destroy();
        
         } // j
       }   // i
    }      // train_algo
}
 





/***********************
training algorithm function :  TRAIN_RPROP
        activation_function :  LINEAR_PIECE_SYMMETRIC
        activation_function :  SIGMOID_SYMMETRIC
                 num_layers =  3
         num_neurons_hidden =  200
              desired_error =  0.01
                        MSE :  0.009016926400363445
                     result :  [ -0.23558363318443298 ]
  --- save ann model --- 
************************/
function act  () 
{
          fann.create_standard_array( parseInt( num_layers ), layers  );


          fann.set_training_algorithm( 2 );
          fann.set_learning_momentum(0.1)

          fann.set_activation_function_hidden( 13 );
          fann.set_activation_function_output( 5 );	// FANN_SIGMOID_STEPWISE	
 
          fann.train_on_data( train_data, 100, 50, 0.01 );
          var MSE = fann.get_MSE();
          var result = fann.run( testdata );

/************************
         console.log( 'training algorithm function : ', training_algorithm_list[train_algo] )
         console.log( '        activation_function : ', activation_function_list[i] )
         console.log( '        activation_function : ', activation_function_list[j] )
*******************/
         console.log( '                 num_layers = ', num_layers) ;
         console.log( '         num_neurons_hidden = ', num_neurons_hidden );
         console.log( '              desired_error = ', desired_error );
         console.log( '                        MSE : ', MSE );
         console.log( '                     result : ', result   );

           if( parseFloat(MSE) < 0.1 )
           {
                console.log( '  --- save ann model --- ' );
               fann.save('./bmw_'+ activation_function_list[i] + '.net');
            }
           console.log( );

           fann.destroy();


}




 act_function () 


// act();

