--main = putStrLn "Hello, World!"

{-
main = do
    putStrLn "Hello, what's your name?"
    name <- getLine
    putStrLn ("Hey " ++ name ++ ", you rock!")
-}

{-
main = do
    putStrLn "Hello, what's your name?"
    name <- getLine
    putStrLn $ "Read this carefully, because this is your future: " ++ name
-}


doubleMe x = x + x


doubleUs x y = doubleMe x + doubleMe y


doubleSmallNumber x = if x > 100 
    then x
    else x * 2


doubleSmallNumber' x = (if x > 100 then x else x*2) + 1


gnekiah'Hsiung = "My name is Gnekiah Hsiung!"


length' xs = sum [1 | _ <- xs]


removeNonUppercase st = [ c | c <- st, c `elem` ['A'..'Z']]
