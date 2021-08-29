`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    20:09:21 06/02/2021 
// Design Name: 
// Module Name:    mux32two 
// Project Name: 
// Target Devices: 
// Tool versions: 
// Description: 
//
// Dependencies: 
//
// Revision: 
// Revision 0.01 - File Created
// Additional Comments: 
//
//////////////////////////////////////////////////////////////////////////////////
module MUX32_2_1(out_data,in1,in2,sel
	);
input [31:0] in1,in2;
input sel;
output [31:0] out_data;

assign out_data = sel?in2:in1;

endmodule
