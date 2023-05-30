----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 03/16/2023 09:41:04 AM
-- Design Name: 
-- Module Name: regfile - Behavioral
-- Project Name: 
-- Target Devices: 
-- Tool Versions: 
-- Description: 
-- 
-- Dependencies: 
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
-- 
----------------------------------------------------------------------------------


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity regfile is
    Port ( ra1 : in STD_LOGIC_VECTOR (2 downto 0);
           ra2 : in STD_LOGIC_VECTOR (2 downto 0);
           wra : in STD_LOGIC_VECTOR (2 downto 0);
           wrd : in STD_LOGIC_VECTOR (15 downto 0);
           clk : in STD_LOGIC;
           rd1 : out STD_LOGIC_VECTOR (15 downto 0);
           rd2 : out STD_LOGIC_VECTOR (15 downto 0);
           w_en : in STD_LOGIC);
end regfile;

architecture Behavioral of regfile is

type reg_array is array (0 to (2**4)-1) of std_logic_vector(15 downto 0);
signal reg_file : reg_array:= (others => x"0000");
begin
process(clk)
begin
  if rising_edge(clk) then
    if w_en = '1' then
        reg_file(conv_integer(wra)) <= wrd;
    end if;
  end if;
 end process;
rd1 <= reg_file(conv_integer(ra1));
rd2 <= reg_file(conv_integer(ra2));
end Behavioral;