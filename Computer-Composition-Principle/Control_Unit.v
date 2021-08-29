`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    19:35:49 06/23/2021 
// Design Name: 
// Module Name:    Control_Unit 
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
module Control_Unit(op,func,RegDst,RegWrite,ALUSrc,MemWrite,MemRead,MemtoReg,Branch,ALU_op
    );
input [5:0] op,func;
output RegDst,RegWrite,ALUSrc,MemWrite,MemRead,MemtoReg,Branch;
output [2:0] ALU_op;

wire [1:0] ALUctr;
Control u0(.op(op),.RegDst(RegDst),.RegWrite(RegWrite),.ALUSrc(ALUSrc),.MemWrite(MemWrite),.MemRead(MemRead),.MemtoReg(MemtoReg),.Branch(Branch),.ALUctr(ALUctr));
ALUOp u1(.func(func),.ALUctr(ALUctr),.ALU_op(ALU_op));


endmodule
