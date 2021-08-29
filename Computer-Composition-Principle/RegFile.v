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
	
	reg [31:0] regfile[1:31]; //����31��32λ�ļĴ���
	
  //�����ݣ���ַ��Ϊ��ʱ����
	assign A = (Rn1 == 0)? 0 : regfile[Rn1];
	assign B = (Rn2 == 0)? 0 : regfile[Rn2];
 
  //д���ݣ������أ�д�ź���Ч��д��ֵ��Ϊ��ʱд��
	always @ (posedge clk) begin
		if ((Write)&&( Wn != 0)) regfile[Wn] = Wd;
	end
  
endmodule
