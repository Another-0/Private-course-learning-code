`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    20:26:55 06/23/2021 
// Design Name: 
// Module Name:    ALUOp 
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
module ALUOp(ALUctr,func,ALU_op
    );
input [1:0] ALUctr;
input [5:0] func;
output [2:0] ALU_op;

reg [2:0] ALU_op;

always@(ALUctr or func)
begin
	if(ALUctr!=2'b10)
	begin
	case(ALUctr)
	2'b00:ALU_op=3'b000;
	2'b01:ALU_op=3'b100;
	2'b11:ALU_op=3'b110;
	default:ALU_op=3'b111;
	endcase
	end
	else
	begin
		case(func)
		6'b100000:ALU_op=3'b000;
		6'b100010:ALU_op=3'b100;
		6'b100100:ALU_op=3'b001;
		6'b100101:ALU_op=3'b101;
		6'b100110:ALU_op=3'b010;
		default:ALU_op=3'b111;
		endcase
	end
end
endmodule
