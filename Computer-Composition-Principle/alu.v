`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    20:42:54 06/02/2021 
// Design Name: 
// Module Name:    alu 
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
module alu(a,b,op,result,zero
    );
input [31:0] a,b;
input [2:0] op;
output [31:0] result;
output zero;

reg [31:0] result;

always@(a or b or op)
begin
    case(op)
    3'b000:result=a+b;
	 3'b100:result=a-b;
	 3'b001:result=a&b;
	 3'b101:result=a|b;
	 3'b010:result=a^b;
	 3'b110:result={b[15:0],16'h0000};
	 default result=32'hxxxxxxxx;
	 endcase
end

reg zero;

always@(result)
begin
	if(!result)zero=1;
		else zero=0;
end

endmodule
