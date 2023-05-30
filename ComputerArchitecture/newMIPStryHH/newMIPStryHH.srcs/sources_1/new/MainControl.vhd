library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity MainControl is
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
end MainControl;

architecture Behavioral of MainControl is
begin

    process(opCode)
    begin
        regDst <= '0'; 
        extOp <= '0'; 
        aluSrc <= '0'; 
        branch <= '0'; 
        jmp <= '0';
        memoryWrite <= '0';
        memoryToRegister <= '0';
        registerWrite <= '0';
         aluOps <= "000";
        case (opCode) is 
            when "000" => -- R type
            regDst <= '1';
            registerWrite <= '1';
                aluOps <= "000";
            when "001" => -- ADDI
            extOp <= '1';
            aluSrc <= '1';
            registerWrite <= '1';
                aluOps <= "001";
            when "010" => -- LW
            extOp <= '1';
            aluSrc <= '1';
            memoryToRegister <= '1';
            registerWrite <= '1';
                aluOps <= "001";
            when "011" => -- SW
            extOp <= '1';
            aluSrc <= '1';
            memoryWrite <= '1';
                aluOps <= "001";
            when "100" => -- BEQ
            extOp <= '1';
            branch <= '1';
            aluOps <= "010";
            when "101" => -- SUBI
            extOp <= '1';
            aluSrc <= '1';
            registerWrite <= '1';
            aluOps <= "101";
            when "110" => -- SLTI
            extOp <= '1';
            aluSrc <= '1';
            registerWrite <= '1';
            aluOps <= "110";
            when "111" => -- J
            jmp <= '1';
            when others => 
            regDst <= '0';
            extOp <= '0'; 
            aluSrc <= '0'; 
            branch <= '0'; 
            jmp <= '0';
            memoryWrite <= '0';
            memoryToRegister <= '0';
            registerWrite <= '0';
                 aluOps <= "000";
        end case;
    end process;		

end Behavioral;




