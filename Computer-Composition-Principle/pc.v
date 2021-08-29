`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    20:23:19 06/16/2021 
// Design Name: 
// Module Name:    pc 
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
module pc(d,rst,clk,pc);
input [31:0] d;
input rst,clk;
output [31:0] pc;

reg [31:0] pc;

always@(posedge clk)
if(!rst) pc<=0;
	else pc<=d;
	
endmodule
