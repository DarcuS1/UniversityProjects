library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity DataMemory is
    port ( clk : in STD_LOGIC;
           enable : in STD_LOGIC;
           aluIn : in STD_LOGIC_VECTOR(15 downto 0);
           rd2 : in STD_LOGIC_VECTOR(15 downto 0);
           memoryWrite : in STD_LOGIC;			
           memorydata : out STD_LOGIC_VECTOR(15 downto 0);
           aluOutput : out STD_LOGIC_VECTOR(15 downto 0));
end DataMemory;

architecture Behavioral of DataMemory is

type mem_type is array (0 to 31) of STD_LOGIC_VECTOR(15 downto 0);
signal mem_DATA : mem_type := (
    others => X"0000");

begin


    process(clk) 			
    begin
        if rising_edge(clk) then
            if enable = '1' then
                if memoryWrite='1' then
                mem_DATA(conv_integer(aluIn(4 downto 0))) <= rd2;			
            end if;
            end if;
        end if;
    end process;

    memorydata <= mem_DATA(conv_integer(aluIn(4 downto 0)));
    aluOutput <= aluIn;

end Behavioral;