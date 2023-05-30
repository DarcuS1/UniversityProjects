library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity instrFetch is
    Port (clk: in STD_LOGIC;
          rst : in STD_LOGIC;
          enable : in STD_LOGIC;
          branch : in STD_LOGIC_VECTOR(15 downto 0);
          jumpAdr : in STD_LOGIC_VECTOR(15 downto 0);
          jmp : in STD_LOGIC;
          pcSrc : in STD_LOGIC;
          instruction : out STD_LOGIC_VECTOR(15 downto 0);
          nextPC : out STD_LOGIC_VECTOR(15 downto 0));
end instrFetch;

architecture Behavioral of instrFetch is
type romTypeSIgnal is array (0 to 255) of STD_LOGIC_VECTOR (15 downto 0);
signal instructionVault : romTypeSIgnal := (
   B"001_000_001_0001011",     -- ADDI $1, $0, 11   1
   B"101_001_001_0000001",     -- SUBI $1, S1, 1     2
   B"001_001_001_0000001",     -- ADDI $1, $1, 1    3 
   B"001_001_001_0001001",      --ADDI $1, $1, 9    4
   B"001_000_010_0010100",      --ADDI $2, $2, 20    5
   B"100_001_010_0000111",      -- BEQ $1, $2, 7    6
   B"000_010_010_010_0_110",    -- XOR $2, $2, $2   11
   B"001_000_001_0000111",     -- ADDI $1, $0, 3    7
   B"000_001_001_001_1_011",    -- SRL $1, $1, 1    8
   B"000_001_001_001_1_010",    -- SLL $1, $1, 1    9
   B"011_001_010_0000000",      -- SW $2, 0($1)     10
   B"000_001_001_001_0_110",    -- XOR $1, $1, $1   11
   B"010_010_001_0000000",     -- LW $2, 0($1)      12
   B"111_0000000000111",       -- J 7              13
    others => X"0000");

signal pcSignal : STD_LOGIC_VECTOR(15 downto 0) := (others => '0');
signal pcSignalAux: STD_LOGIC_VECTOR(15 downto 0):= (others => '0');
signal pcPlusOne: STD_LOGIC_VECTOR(15 downto 0):= (others => '0');
signal tempBrd: STD_LOGIC_VECTOR(15 downto 0):= (others => '0');

begin
    process(clk)
    begin
        if rising_edge(clk) then
            if rst = '1' then
                pcSignal <= x"0000";
            elsif enable = '1' then
                pcSignal <= pcPlusOne;
            end if;
        end if;
    end process;

    instruction <= instructionVault(conv_integer(pcSignal(7 downto 0)));
    pcSignalAux <= pcSignal + 1;
    nextPC <= pcSignalAux;

    process(pcSrc, pcSignalAux, branch)
    begin
        if pcSrc = '1' then
            tempBrd <= branch;
            else 
            tempBrd <= pcSignalAux;
            end if;
    end process;	

    process(jmp, tempBrd, jumpAdr)
    begin
        if jmp = '1' then 
        pcPlusOne <= jumpAdr;
        else
        pcPlusOne <= tempBrd;
        end if;
    end process;

end Behavioral;