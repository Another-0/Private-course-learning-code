`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    21:26:46 06/23/2021 
// Design Name: 
// Module Name:    CPU 
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
module CPU(clk,rst,addr,result);
	input clk ,rst;
	output [31:0] addr,result;

	wire [31:0] Inst,Wd, A, B, InstExtnd, SrcB, ALURes, ReadData;
	wire RegDst, RegWrite, ALUSrc, MemWrite, MemRead, MemToReg, Branch, Zero;
	wire [2:0] ALU_op;
	wire [4:0] Wn;

	assign result = ALURes;

	fetch u0(.clk(clk),.rst(rst),.Z(Zero),.B(Branch),.B_addr(InstExtnd),.addr(addr));
	INST_ROM u1(.addr(addr),.Inst(Inst));
	Control_Unit u2( .op(Inst[31:26]) , .func(Inst[5:0]), .RegDst(RegDst), .RegWrite(RegWrite), .ALUSrc(ALUSrc), .MemWrite(MemWrite),.MemRead(MemRead), .MemtoReg(MemtoReg), .Branch(Branch), .ALU_op(ALU_op));

	assign Wn = RegDst ? Inst[15:11] : Inst[20:16];

	RegFile u3(.clk(clk), .Rn1(Inst[25:21]), .Rn2(Inst[20:16]), .Wn(Wn), .Wd(Wd), .Write(RegWrite), .A(A), .B(B));
	extnd u4(.data_16bit(Inst[15:0]), .data_32bit(InstExtnd));
	MUX32_2_1 u5(.out_data(SrcB), .in1(B), .in2(InstExtnd), .sel(ALUSrc));
	alu u6(.a(A), .b(SrcB), .op(ALU_op), .result(ALURes), .zero(Zero));
	DATA_RAM u7(.Clock(clk), .dataout(ReadData), .datain(B), .addr(ALURes), .write(MemWrite), .read(MemRead));
	MUX32_2_1 u8(.out_data(Wd), .in1(ALURes), .in2(ReadData), .sel(MemtoReg));
	
endmodule