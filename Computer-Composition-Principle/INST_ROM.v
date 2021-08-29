`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    19:35:57 12/17/2017 
// Design Name: 
// Module Name:    INST_ROM 
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
module INST_ROM(
	 input [31:0] addr,
	 output [31:0] Inst
    );
	 
	 wire [31:0] ram [31:0];
	 
	 assign ram[5'h00]=0;    				//
	 assign ram[5'h01]=32'h3c010003;    //lui R1,0x0003
	 assign ram[5'h02]=32'h3c020001;    //lui R2,0x0001
	 assign ram[5'h03]=32'h10220000;    //beq R1,R2,0
	 assign ram[5'h04]=32'h00221824;    //and R3,R1,R2
 	 assign ram[5'h05]=32'h00221820;    //add R3,R1,R2
	 assign ram[5'h06]=32'h00221825;    //or R3,R1,R2
	 assign ram[5'h07]=32'h00221826;    //xor R3,R1,R2
	 assign ram[5'h08]=32'hac610064;    //sw R1,100(R3)
	 assign ram[5'h09]=32'h00222222;    //sub R4,R1,R2
	 assign ram[5'h0a]=32'h8c640064;    //lw R4,100(R3)
	 assign ram[5'h0b]=32'h10240003;    //beq R1,R4,0x0003

	 assign Inst=ram[addr[6:2]];

endmodule
