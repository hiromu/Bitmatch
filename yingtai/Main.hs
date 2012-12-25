import Control.Applicative
import Control.Monad
import Data.Bits
import Data.Maybe
import System.IO
import System.Random

data LR = L | R deriving Eq

type Fingers = Int
type GameState = ((Fingers,LR), (Fingers,LR))
type Out = Maybe (GameState, Int)

toFingers xs = foldr1 (\x y -> x + 2*y) $ reverse xs 

check :: GameState -> Out 
check ((my,p),(ot,q))
  = case catMaybes $ check'<$>[-3..3] of
      []    -> Nothing
      (x:_) -> Just x
  where
    check' n | no `elem` [7,14,15] = Just (((my,p),(no,q)),n)
             | otherwise = Nothing
      where nmy = shift my n `mod` 8
            no  = nmy `xor` ot

putDice :: Int -> Int -> IO ()
putDice x y = getStdRandom (randomR (x,y)) >>= putStr.show

getList :: IO Fingers 
getList = toFingers.map read.words<$>getLine

main = forever $ do
  _ <- getLine
  myL <- getList 
  myR <- getList
  otL <- getList
  otR <- getList
  let comb = [(x,y) | x <- [(myL,L),(myR,R)], y <- [(otL,L),(otR,R)]]
  case catMaybes $ check<$>comb of
    [] -> putDice 0 1 >> putChar ' ' >> putDice 0 1 >> putChar ' ' >> putDice (-3) 3 >> putStrLn "" 
    ((((nmy,p),(no,q)),n):_) -> do
        if p == L then putStr "0 "
                  else putStr "1 "
        if q == L then putStr "0 "
                  else putStr "1 "
        print n
  hFlush stdout
  main
