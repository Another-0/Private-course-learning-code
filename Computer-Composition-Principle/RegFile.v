`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    19:13:54 06/30/2021 
// Design Name: 
// Module Name:    RegFile 
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
module RegFile(clk,Rn1,Rn2,Wn,Wd,Write,A,B);
	input clk;
	input [4:0] Rn1,Rn2,Wn;
	input [31:0] Wd;
	input Write;
	output [31:0] A,B;
	
	reg [31:0] regfile[1:31]; //定义31个32位的寄存器
	
  //读数据（地址不为零时读）
	assign A = (Rn1 == 0)? 0 : regfile[Rn1];
	assign B = (Rn2 == 0)? 0 : regfile[Rn2];
 
  //写数据（上升沿，写信号有效，写入值不为零时写）
	always @ (posedge clk) begin
		if ((Write)&&( Wn != 0)) regfile[Wn] = Wd;
	end
  
endmodule
