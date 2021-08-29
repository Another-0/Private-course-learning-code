`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    19:56:26 06/16/2021 
// Design Name: 
// Module Name:    quzhi 
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
module fetch(clk,rst,Z,B,B_addr,addr
    );
	 input clk,rst,Z,B;
	 input [31:0] B_addr;
	 output [31:0] addr;
	 
	 reg [31:0] pc;
	 wire [31:0] out1,out2,B_addr1,next_pc;
	 wire sel = Z&B;
	   
	 zuoyi2 u0(.a(B_addr),.b(B_addr1));
	 add2 u1(.a(pc),.b(32'h00000004),.c(out1));
	 add2 u2(.a(out1),.b(B_addr1),.c(out2));
	 MUX32_2_1 u3(.out_data(next_pc),.in1(out1),.in2(out2),.sel(sel));
	 

	 always@(posedge clk)begin
	 if(rst)pc<=0;
		else pc<=next_pc;
	 end
	 assign addr=pc;
	 
endmodule
