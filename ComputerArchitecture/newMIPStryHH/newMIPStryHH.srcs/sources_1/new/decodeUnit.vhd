	   
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

entity decodeUnit is
	Port(	   	
	clk: in std_logic;	   
	wEN: in std_logic;	
	instruction: in std_logic_vector(12 downto 0);
	wRD: in std_logic_vector(15 downto 0);
	regWrite: in std_logic;
	regDst: in std_logic;
	exOpt: in std_logic;		  
	rd1:out std_logic_vector(15 downto 0);
	rd2: out std_logic_vector(15 downto 0);
	extImm: out std_logic_vector(15 downto 0);
	func: out std_logic_vector(2 downto 0);	
	sa: out std_logic
	);
end decodeUnit;

architecture behav of decodeUnit is

component regfile is
    Port ( ra1 : in STD_LOGIC_VECTOR (2 downto 0);
           ra2 : in STD_LOGIC_VECTOR (2 downto 0);
           wra : in STD_LOGIC_VECTOR (2 downto 0);
           wrd : in STD_LOGIC_VECTOR (15 downto 0);
           clk : in STD_LOGIC;
           rd1 : out STD_LOGIC_VECTOR (15 downto 0);
           rd2 : out STD_LOGIC_VECTOR (15 downto 0);
           w_en : in STD_LOGIC);
end component;

signal muxInstr: std_logic_vector(2 downto 0):=(others=>'0');
signal extSignal: std_logic_vector(15 downto 0):=(others=>'0');

begin  
	
	process(clk,regDst, instruction)
	begin
		
		if(regDst='1') then 
			muxInstr<=instruction(6 downto 4);
		else 
			muxInstr<=instruction(9 downto 7);
		end if;
		end process;
		
		
		process(clk,instruction, exOpt)
		begin	 	
			if(exOpt='1') then
				if instruction(6)='1' then 
					extSignal<="111111111"&instruction(6 downto 0);
				else 
					extSignal<="000000000"&instruction(6 downto 0);		  
				end if;
			else 
				extSignal<="000000000"&instruction(6 downto 0);	 
			end if;		
				
				end process;
			
				extImm<=extSignal;
				func<=instruction(2 downto 0);
				sa<=instruction(3);
	regfile1: regfile port map(instruction(12 downto 10), instruction(9 downto 7), muxInstr, wRD, clk, rd1, rd2, wEN);


end behav;