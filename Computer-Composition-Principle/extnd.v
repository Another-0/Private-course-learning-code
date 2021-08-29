`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    20:38:07 06/02/2021 
// Design Name: 
// Module Name:    extnd 
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
module extnd(data_16bit,data_32bit
    );
input [15:0] data_16bit;
output [31:0] data_32bit;

assign data_32bit={{16{data_16bit[15]}},data_16bit};

endmodule
