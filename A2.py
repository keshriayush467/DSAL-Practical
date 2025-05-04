class Set:
 
  def __init__(self):
      self.element = []
      
  def add(self,new_element):
      if new_element not in self.element:
          self.element.append(new_element)
          
  def remove(self,element):
      if element in self.element:
          self.element.remove(element)
          
  def contain(self, element):
      return element in self.element
  
  def size(self):
      return len(self.element)
  
  def intersection(self,other):
      result = Set()
      for elem in self.element:
          if elem in other.element:
              result.add(elem)
      return result
  
  def union(self,other):
      result = Set()
      result.element = self.element.copy()
      for elem in self.element:
          if elem not in result.element:
              result.add(elem)
      return result
  
  def difference(self,other):
      result = Set()
      for elem in self.element:
          if elem not in other.element:
              result.add(elem)
      return result
  
  def subset(self,other):
      for elem in self.element:
          if elem in other.element:
              return True
      return False
  
  def display(self):
      print("".join(map(str,self.element)))
      
   
def set_Operations(set1,set2):
      while True:
          print("\n1. Add Element in Set 1")
          print("\n2. Add Element in Set 2")
          print("\n3. Remove Element in Set 1")
          print("\n4. Remove Element in Set 2")
          print("\n5. Display Element in Set 1")
          print("\n6. Display Element in Set 2")
          print("\n7. Intersection of Set 1 & Set 2")
          print("\n8. Union of Set 1 & Set 2")
          print("\n9. Difference of Set 1 & Set 2")
          print("\n10. Check if Set 1 is subset Set 2")
          print("\n11. Exit")
          
          choice = int(input("\nEnter ur choice "))
          
          if(choice==1):
              element = int(input("\nEnter the element in set 1 "))
              set1.add(element)
              
          elif(choice==2):
              element = int(input("\nEnter the element in set 2 "))
              set2.add(element)
              
          elif(choice==3):
              element = int(input("\nEnter the element to be removed in Set 1"))
              set1.remove(element)
              
          elif(choice==4):
              element = int(input("\nEnter the element to be removed in Set 2"))
              set2.remove(element)
              
          elif(choice==5):
              print("\nSet 1 :",set1.display())
              
          elif(choice==6):
              print("\nSet2 :", set2.display())
              
          elif(choice==7):
              intersect_set=set1.intersection(set2)
              print("\nIntersection of Set 1 & Set 2 ",end="")
              intersect_set.display()
              
          elif(choice==8):
              union_set=set1.union(set2)
              print("\nUnion of Set 1 & Set 2 ",end="")
              union_set.display()
              
          elif(choice==9):
              diff_set=set1.difference(set2)
              print("\nDifference of Set 1 & Set 2 ",end="")
              diff_set.display()
              
          elif(choice==10):
              if set1.subset(set2):
                  print("\nSubset of Set 1 is set 2")
              else:
                  print('\nSet 1 is not Subset of Set 2')
                  
          elif(choice==11):
              print("\nExiting ")
              
              break
          else:
              print("\nInvalid choice")
              
if __name__ == "__main__":
      set1 =Set()
      set2 = Set()
      set_Operations(set1,set2)                 
              
      
      
      