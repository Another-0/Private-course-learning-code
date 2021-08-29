`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    19:43:50 06/23/2021 
// Design Name: 
// Module Name:    Control 
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
module Control(op,RegDst,RegWrite,ALUSrc,MemWrite,MemRead,MemtoReg,Branch,ALUctr
    );
input [5:0] op;
output RegDst,RegWrite,ALUSrc,MemWrite,MemRead,MemtoReg,Branch;
output [1:0] ALUctr;

reg RegDst,RegWrite,ALUSrc,MemWrite,MemRead,MemtoReg,Branch;
reg [1:0] ALUctr;

always@(op)
begin
case(op)
6'b000000:begin RegDst=1;RegWrite=1;ALUSrc=0;MemWrite=0;MemRead=0;MemtoReg=0;Branch=0;ALUctr=2'b10;end
6'b100011:begin RegDst=0;RegWrite=1;ALUSrc=1;MemWrite=0;MemRead=1;MemtoReg=1;Branch=0;ALUctr=2'b00;end
6'b101011:begin RegDst=0;RegWrite=0;ALUSrc=1;MemWrite=1;MemRead=0;MemtoReg=0;Branch=0;ALUctr=2'b00;end
6'b000100:begin RegDst=0;RegWrite=0;ALUSrc=0;MemWrite=0;MemRead=0;MemtoReg=0;Branch=1;ALUctr=2'b01;end
6'b001111:begin RegDst=0;RegWrite=1;ALUSrc=1;MemWrite=0;MemRead=0;MemtoReg=0;Branch=0;ALUctr=2'b11;end
default:begin RegDst=0;RegWrite=0;ALUSrc=0;MemWrite=0;MemRead=0;MemtoReg=0;Branch=0;ALUctr=2'b00;end
endcase
end
endmodule
