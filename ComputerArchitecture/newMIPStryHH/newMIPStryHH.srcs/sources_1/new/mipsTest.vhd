library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity mipsTEST is
    Port ( clk : in STD_LOGIC;
           btn : in STD_LOGIC_VECTOR (4 downto 0);
           sw : in STD_LOGIC_VECTOR (15 downto 0);
           led : out STD_LOGIC_VECTOR (15 downto 0);
           an : out STD_LOGIC_VECTOR (3 downto 0);
           cat : out STD_LOGIC_VECTOR (6 downto 0));
end mipsTEST;

architecture Behavioral of mipsTEST is

component MPG is
    Port ( en : out STD_LOGIC;
           input : in STD_LOGIC;
           clock : in STD_LOGIC);
end component;

component SSD is
    Port ( clk: in STD_LOGIC;
           digits: in STD_LOGIC_VECTOR(15 downto 0);
           an: out STD_LOGIC_VECTOR(3 downto 0);
           cat: out STD_LOGIC_VECTOR(6 downto 0));
end component;

component instrFetch
Port (clk: in STD_LOGIC;
rst : in STD_LOGIC;
enable : in STD_LOGIC;
branch : in STD_LOGIC_VECTOR(15 downto 0);
jumpAdr : in STD_LOGIC_VECTOR(15 downto 0);
jmp : in STD_LOGIC;
pcSrc : in STD_LOGIC;
instruction : out STD_LOGIC_VECTOR(15 downto 0);
nextPC : out STD_LOGIC_VECTOR(15 downto 0));
end component;


component decodeUnit is
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
end component;

component MainControl
Port ( opCode : in STD_LOGIC_VECTOR(2 downto 0);
regDst : out STD_LOGIC;
extOp : out STD_LOGIC;
aluSrc : out STD_LOGIC;
branch : out STD_LOGIC;
jmp : out STD_LOGIC;
aluOps : out STD_LOGIC_VECTOR(2 downto 0);
memoryWrite : out STD_LOGIC;
memoryToRegister : out STD_LOGIC;
registerWrite : out STD_LOGIC);
end component;

component ExecutionUnit is
    Port ( nextPC : in STD_LOGIC_VECTOR(15 downto 0);
           rd1 : in STD_LOGIC_VECTOR(15 downto 0);
           rd2 : in STD_LOGIC_VECTOR(15 downto 0);
           imm : in STD_LOGIC_VECTOR(15 downto 0);
           func : in STD_LOGIC_VECTOR(2 downto 0);
           sa : in STD_LOGIC;
           aluSrc : in STD_LOGIC;
           aluOps : in STD_LOGIC_VECTOR(2 downto 0);
           branch : out STD_LOGIC_VECTOR(15 downto 0);
           aluOut : out STD_LOGIC_VECTOR(15 downto 0);
           zFlag : out STD_LOGIC);
end component;

component DataMemory
port ( clk : in STD_LOGIC;
enable : in STD_LOGIC;
aluIn : in STD_LOGIC_VECTOR(15 downto 0);
rd2 : in STD_LOGIC_VECTOR(15 downto 0);
memoryWrite : in STD_LOGIC;			
memorydata : out STD_LOGIC_VECTOR(15 downto 0);
aluOutput : out STD_LOGIC_VECTOR(15 downto 0));
end component;

signal instr, nextPC, rd1, rd2, writeData, imm : STD_LOGIC_VECTOR(15 downto 0); 
signal jmpAdr, branchAdr, aluRes, aluRes2, memoryData : STD_LOGIC_VECTOR(15 downto 0);


signal func : STD_LOGIC_VECTOR(2 downto 0);
signal sa, zero : STD_LOGIC;
signal outputLEDS : STD_LOGIC_VECTOR(15 downto 0);
signal en, rst, pcSrc : STD_LOGIC; 


signal RegDst, ExtOp, ALUSrc, Branch, Jump, MemWrite, MemtoReg, RegWrite : STD_LOGIC;
signal ALUOp :  STD_LOGIC_VECTOR(2 downto 0);

begin


    mpg1: MPG port map(en, btn(0), clk);
    mpg2: MPG port map(rst, btn(1), clk);
    

    instructionFetch: instrFetch port map(clk, rst, en, branchAdr, jmpAdr, Jump, pcSrc, instr, nextPC);
    executionUnitt: ExecutionUnit port map(nextPC, rd1, rd2, imm, func, sa, ALUSrc, ALUOp, branchAdr, aluRes, Zero); 
    memory: DataMemory port map(clk, en, aluRes, rd2, MemWrite, memoryData, aluRes2);
    decodeUnitt: decodeUnit port map(clk, en, instr(12 downto 0), writeData, RegWrite, RegDst, ExtOp, rd1, rd2, imm, func, sa);
    controlUnit: MainControl port map(instr(15 downto 13), RegDst, ExtOp, ALUSrc, Branch, Jump, ALUOp, MemWrite, MemtoReg, RegWrite);
   

    process(MemtoReg)
    begin
    if MemtoReg = '1' then
        writeData <= memoryData;
    elsif MemtoReg = '0' then
        writeData <= aluRes2;
    else
        writeData <= (others => '0');
    end if;
    end process;

    pcSrc <= Zero and Branch;
    jmpAdr <= nextPC(15 downto 13) & instr(12 downto 0);
    --"000" & instr(12 downto 0) - x"0001";

 process(sw)
 begin
    case sw(2 downto 0) is
        when "000" =>
            outputLEDS <= instr;
        when "001" =>
            outputLEDS <= rd1;
        when "010" =>
            outputLEDS <= rd2;
        when "011" =>
            outputLEDS <= nextPC;
        when "100" =>
            outputLEDS <= imm;
        when "101" =>
            outputLEDS <= memoryData;
        when "110" =>
            outputLEDS <= writeData;
        when "111" =>
            outputLEDS <= aluRes;
        when others =>
            outputLEDS <= (others => '0');
    end case;
    end process;
    
    output : SSD port map (clk, outputLEDS, an, cat);

    led(10 downto 0) <= ALUOp & ALUSrc & Branch & Jump & RegDst & ExtOp & MemWrite & MemtoReg & RegWrite;
    
end Behavioral;