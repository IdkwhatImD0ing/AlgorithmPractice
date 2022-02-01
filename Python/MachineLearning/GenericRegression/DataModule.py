from typing import List, Tuple

import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
from sklearn.model_selection import train_test_split
from tqdm.notebook import trange

class DataModule:
    def __init__(self) -> None:
        """
        Inits data module with dataset url and column names. Do not modify.
        """
        self.url = "http://archive.ics.uci.edu/ml/machine-learning-databases/auto-mpg/auto-mpg.data"
        self.column_names = [
            "mpg",
            "cylinders",
            "displacement",
            "horsepower",
            "weight",
            "acceleration",
            "model_year",
            "origin",
        ]

    def load_data(self) -> None:
        """
        Load the dataset and drop NaN rows. Do not modify.
        """
        self.dataset = pd.read_csv(
            self.url,
            names=self.column_names,
            na_values="?",
            comment="\t",
            sep=" ",
            skipinitialspace=True,
        ).dropna()
        #print(type(self.dataset))
        #print(self.dataset)
        #print(self.column_names)

    def bin_feature(self, feature: str, bins: pd.IntervalIndex) -> None:
        """
        Perform binning operation on the column named "feature" in the given
        dataframe, and encode the binned feature into one-hot vectors.

        Args:
            feature: Name of the feature to bin.
            bins: Bin intervals represented by pd.IntervalIndex.
        """


        self.dataset[feature+'_bin'] = pd.cut(self.dataset[feature], bins = bins)
        self.dataset = pd.get_dummies(self.dataset, columns=[feature+'_bin'])
        #print(self.dataset)


    def one_hot_encode(self, features: List[str]) -> None:
        """
        Encode a list of features in a dataframe as one-hot vectors and drop the
        (original) unencoded feature columns.

        Args:
            features: The column names of the features that need to be encoded.
        """


        for x in features:
            encoded_data = pd.get_dummies(self.dataset[x], prefix = x)
            self.dataset = self.dataset.drop(x, axis = 1)
            self.dataset = self.dataset.join(encoded_data)
            #print("--------- encoding " + x + "---------")
            #print(self.dataset.columns)
            #print(self.dataset)
            #print(encoded_data)

        #print(self.dataset.columns)
        #print(self.dataset)
        


    def cross_feature(self, feature_a: str, feature_b: str) -> None:
        """
        Make a new crossed feature by multiplying feature_a and feature_b, and
        name the new feature as "crossed_feature".

        Args:
            feature_a: The column name of feature A.
            feature_b: The column name of feature B.
        """


        self.dataset["crossed_feature"] = self.dataset[feature_a] * self.dataset[feature_b]
        #print(self.dataset)



    def normalize(self) -> None:
        """
        Use min-max normalizaton to normlaize the dataset. The equation is provided below.

        d_normalized = (d - min(d)) / (max(d) - min(d))
        """

        for column in self.dataset.columns:
            self.dataset[column] = (self.dataset[column] - self.dataset[column].min())/(self.dataset[column].max() - self.dataset[column].min())
        



    def train_val_test_split(
        self, val_size: float = 0.2, test_size: float = 0.5, seed: int = 144
    ) -> Tuple[Tuple[np.ndarray], Tuple[np.ndarray], Tuple[np.ndarray]]:
        """
        Split a dataframe into features and labels for train, validation, and test sets.

        DO NOT modify the default parameters specified above, and make sure to turn on
        shuffling by shuffle=True.

        More specifically, you are supposed to first split 50% of all data into the test
        set, and then the other 50% as the training set. For the training set, you should
        then use the given 80%/20% split as train/validation.

                               |--------|       |--|      |----------|
                               train (156)    val (40)     test (196)

        You should have 156/40/196 examples in train/val/test, respectively. And do not
        forget to split features from labels at the end.

        Args:
            val_size: The proportion of the dataset to include in the validation set.
            It must be a float type.

            test_size: The proportion of the dataset to include in the validation set. It
            must be a float type.

            seed: Controls the shuffling of the dataframe. Do not modify the default seed.

        Returns:
            A tuple containing train, validation, and test features and labels.
        """

        #print("-----------SPLITTING------------")
        train, test = train_test_split(self.dataset, test_size = test_size, random_state = seed, shuffle = True)
        #print(train)
        #print(test)

        train, val = train_test_split(train, test_size = val_size, random_state = seed, shuffle = True)
        #print(train)
        #print(val)
        y_train = train["mpg"]
        train = train.drop("mpg", axis = 1)
        x_train = train.to_numpy()
        
        y_val = val["mpg"]
        val = val.drop("mpg", axis = 1)
        x_val = val.to_numpy()
        
        y_test = test["mpg"]
        test = test.drop("mpg", axis = 1)
        x_test = test.to_numpy()
        
        



        return (
            (x_train, y_train),
            (x_val, y_val),
            (x_test, y_test),
        )