`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    21:29:14 06/16/2021 
// Design Name: 
// Module Name:    zuoyi2 
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
module zuoyi2(a,b
    );
input [31:0] a;
output [31:0] b;
assign b = {a[29:0],2'b00};

endmodule
